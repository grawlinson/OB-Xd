/*
  ==============================================================================

    ScaleComponent.h
    Created: 27 Aug 2021 1:26:08pm
    Author:  discoDSP

  ==============================================================================
*/

#pragma once

//==============================================================================
#include <JuceHeader.h>
class ObxdAudioProcessor;




//==============================================================================
class ScalableComponent
{
public:
    ~ScalableComponent();
    int getScaleInt();
    void setScaleFactor(float newScaleFactor, bool newIsHighResolutionDisplay);
    float getScaleImage();
    float getScaleFactor() const;
	bool getIsHighResolutionDisplay() const;

    virtual void scaleFactorChanged();

protected:
    ScalableComponent(ObxdAudioProcessor* owner_);

    Image getScaledImageFromCache(const String& imageName, float scaleFactor, bool isHighResolutionDisplay);

private:
    ObxdAudioProcessor* processor;
    float scaleFactor;
	bool isHighResolutionDisplay;
    
};


//==============================================================================
class CustomLookAndFeel : public LookAndFeel_V3,
                             public ScalableComponent
{
public:
    CustomLookAndFeel(ObxdAudioProcessor* owner_):LookAndFeel_V3(), ScalableComponent(owner_) {
        this->setColour(PopupMenu::backgroundColourId, Colour(20, 20, 20));
        this->setColour(PopupMenu::textColourId, Colour(245, 245, 245));
        this->setColour(PopupMenu::highlightedBackgroundColourId, Colour(60, 60, 60));
        this->setColour(Label::textColourId, Colour(245, 245, 245));
    };
    

    PopupMenu::Options getOptionsForComboBoxPopupMenu (ComboBox& box, Label& label) override
    {
        PopupMenu::Options option = LookAndFeel_V3::getOptionsForComboBoxPopupMenu(box, label);
        return option.withStandardItemHeight (label.getHeight()/ getScaleFactor());
    };
    Font getPopupMenuFont () override
    {

        float scaleFactor = getScaleFactor();
        DBG("getPopupMenuFont::scaleFactor " << scaleFactor);
        if (scaleFactor > 1.0) scaleFactor *= 0.75;

        
        #ifdef JUCE_MAC
            return Font("Helvetica Neue", 16.0 * scaleFactor, Font::plain);
        #endif
            
        #ifdef JUCE_WINDOWS
            return Font("Arial", 16.0 * scaleFactor, Font::plain);
        #endif

        #ifdef JUCE_LINUX
            return Font("DejaVu Sans", 16.0 * scaleFactor, Font::plain);
        #endif
    }
    /*
    void drawPopupMenuItem (Graphics& g, const Rectangle<int>& area,
                                            const bool isSeparator, const bool isActive,
                                            const bool isHighlighted, const bool isTicked,
                                            const bool hasSubMenu, const String& text,
                                            const String& shortcutKeyText,
                                            const Drawable* icon, const Colour* const textColourToUse)
    {
        if (isSeparator)
        {
            auto r = area.reduced (5, 0);
            r.removeFromTop (r.getHeight() / 2 - 1);

            g.setColour (Colour (0x33000000));
            g.fillRect (r.removeFromTop (1));

            g.setColour (Colour (0x66ffffff));
            g.fillRect (r.removeFromTop (1));
        }
        else
        {
            auto textColour = findColour (PopupMenu::textColourId);

            if (textColourToUse != nullptr)
                textColour = *textColourToUse;

            auto r = area.reduced (1);

            if (isHighlighted)
            {
                g.setColour (findColour (PopupMenu::highlightedBackgroundColourId));
                g.fillRect (r);

                g.setColour (findColour (PopupMenu::highlightedTextColourId));
            }
            else
            {
                g.setColour (textColour);
            }

            if (! isActive)
                g.setOpacity (0.3f);

            Font font (getPopupMenuFont());

            auto maxFontHeight = (float) area.getHeight() / 1.3f;

            if (font.getHeight() > maxFontHeight)
                font.setHeight (maxFontHeight);

            g.setFont (font);

            auto iconArea = r.removeFromLeft ((r.getHeight() * 5) / 4).reduced (3).toFloat();

            if (icon != nullptr)
            {
                icon->drawWithin (g, iconArea, RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.0f);
            }
            else if (isTicked)
            {
                auto tick = getTickShape (1.0f);
                g.fillPath (tick, tick.getTransformToScaleToFit (iconArea, true));
            }

            if (hasSubMenu)
            {
                auto arrowH = 0.6f * getPopupMenuFont().getAscent();

                auto x = (float) r.removeFromRight ((int) arrowH).getX();
                auto halfH = (float) r.getCentreY();

                Path p;
                p.addTriangle (x, halfH - arrowH * 0.5f,
                               x, halfH + arrowH * 0.5f,
                               x + arrowH * 0.6f, halfH);

                g.fillPath (p);
            }

            r.removeFromRight (3);
            g.drawFittedText (text, r, Justification::centredLeft, 1);

            if (shortcutKeyText.isNotEmpty())
            {
                Font f2 (font);
                f2.setHeight (f2.getHeight() * 0.75f);
                f2.setHorizontalScale (0.95f);
                g.setFont (f2);

                g.drawText (shortcutKeyText, r, Justification::centredRight, true);
            }
        }
    }
    void drawLabel (Graphics& g, Label& label) override
    {
        g.fillAll (label.findColour (Label::backgroundColourId));

        if (! label.isBeingEdited())
        {
            auto alpha = label.isEnabled() ? 1.0f : 0.5f;
            const Font font (getLabelFont (label));

            g.setColour (label.findColour (Label::textColourId).withMultipliedAlpha (alpha));
            g.setFont (font);

            auto textArea = getLabelBorderSize (label).subtractedFrom (label.getLocalBounds());
            textArea = textArea.toFloat().transformedBy(AffineTransform::scale(getScaleFactor())).toNearestInt();
            g.drawFittedText (label.getText(), textArea, label.getJustificationType(),
                              jmax (1, (int) ((float) textArea.getHeight() / font.getHeight())),
                              label.getMinimumHorizontalScale());

            g.setColour (label.findColour (Label::outlineColourId).withMultipliedAlpha (alpha));
        }
        else if (label.isEnabled())
        {
            g.setColour (label.findColour (Label::outlineColourId));
        }

        g.drawRect (label.getLocalBounds());
    }
    BorderSize<int> getLabelBorderSize (Label& label)
    {
        BorderSize<int> boder = label.getBorderSize();
        Rectangle<int> rec = Rectangle<int>::leftTopRightBottom(boder.getLeft(), boder.getTop(), boder.getRight(), boder.getBottom());
        Rectangle<int> rec2 = rec.toFloat().transformedBy(AffineTransform::scale(getScaleFactor())).toNearestInt();
        
        return BorderSize<int>(rec2.getX(), rec2.getY(), rec2.getRight(), rec2.getBottom() );
    }
    */
};
