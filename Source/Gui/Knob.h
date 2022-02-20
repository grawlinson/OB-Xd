/*
	==============================================================================
	This file is part of Obxd synthesizer.

	Copyright � 2013-2014 Filatov Vadim
	
	Contact author via email :
	justdat_@_e1.ru

	This file may be licensed under the terms of of the
	GNU General Public License Version 2 (the ``GPL'').

	Software distributed under the License is distributed
	on an ``AS IS'' basis, WITHOUT WARRANTY OF ANY KIND, either
	express or implied. See the GPL for the specific language
	governing rights and limitations.

	You should have received a copy of the GPL along with this
	program. If not, go to http://www.gnu.org/licenses/gpl.html
	or write to the Free Software Foundation, Inc.,  
	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
	==============================================================================
 */
#pragma once
#include "../Source/Engine/SynthEngine.h"
#include "../Components/ScaleComponent.h"
class ObxdAudioProcessor;
class Knob  : public Slider, public ScalableComponent, public ActionBroadcaster
{
    juce::String img_name;
public:
	//Knob(Image image, const int numFrames, const bool stripIsHorizontal) : Slider("Knob")
	//{
		
	//	setTextBoxStyle(NoTextBox, 0, 0, 0);
	//	setSliderStyle(RotaryVerticalDrag);
	//	setRange(0.0f, 1.0f, 0.001f);
	//}
	Knob (juce::String name, int fh, ObxdAudioProcessor* owner_) : Slider("Knob"), ScalableComponent(owner_), img_name(name)
	{
        scaleFactorChanged();
        
		h2 = fh;
        w2 = kni.getWidth();
		numFr = kni.getHeight() / h2;
		
	};
    void scaleFactorChanged() override
    {
        kni = getScaledImageFromCache(img_name, getScaleFactor(), getIsHighResolutionDisplay());
        /*
        backgroundImage =
            allImage.getClippedImage(Rectangle<int>(0,
                                                    allImage.getHeight() / 2,
                                                    allImage.getWidth(),
                                                    allImage.getHeight() / 2));
         */
        repaint();
    }

    void mouseDown(const MouseEvent& event) override
    {
        if (event.mods.isShiftDown())
        {
            if (shouldResetOnShiftClick)
            {
                sendActionMessage(resetActionMessage);
            }
        }
        Slider::mouseDown(event);
    }
// Source: https://git.iem.at/audioplugins/IEMPluginSuite/-/blob/master/resources/customComponents/ReverseSlider.h
public:
    class KnobAttachment  : public juce::AudioProcessorValueTreeState::SliderAttachment
    {
        RangedAudioParameter* parameter = nullptr;
        Knob* sliderToControl = nullptr;
    public:
        KnobAttachment (juce::AudioProcessorValueTreeState& stateToControl,
                        const juce::String& parameterID,
                        Knob& sliderToControl) : AudioProcessorValueTreeState::SliderAttachment (stateToControl, parameterID, sliderToControl), sliderToControl(&sliderToControl)
        {
            parameter = stateToControl.getParameter (parameterID);
            sliderToControl.setParameter (parameter);
        }
        
        
        /*KnobAttachment (juce::AudioProcessorValueTreeState& stateToControl,
                        const juce::String& parameterID,
                        Slider& sliderToControl) : AudioProcessorValueTreeState::SliderAttachment (stateToControl, parameterID, sliderToControl)
        {
        }*/
        
        void updateToSlider(){
            float val = parameter->getValue();
            //sliderToControl->setValue(parameter->convertFrom0to1(val0to1));
            sliderToControl->setValue(val, NotificationType::dontSendNotification);
            //DBG(" Slider: " << parameter->name << " " << sliderToControl->getValue() << "  Parameter: "<< " " << parameter->getValue());
        }
        
        virtual ~KnobAttachment() = default;
    };
    
    void setParameter (AudioProcessorParameter* p)
    {
        if (parameter == p)
            return;
        
        parameter = p;
        updateText();
        repaint();
    }

	void paint (Graphics& g) override
	{
		int ofs = (int) ((getValue() - getMinimum()) / (getMaximum() - getMinimum()) * (numFr - 1));
        g.drawImage (kni, 0, 0, getWidth(), getHeight(), 0, h2 * ofs * getScaleInt(), w2 * getScaleInt(), h2 * getScaleInt());
	}
    
    ~Knob() override {};

    void resetOnShiftClick(bool value, const String& identifier)
    {
        shouldResetOnShiftClick = value;
        resetActionMessage = identifier;
    }
private:
	Image kni;
	int fh, numFr;
	int w2, h2;
    bool shouldResetOnShiftClick{ false };
    String resetActionMessage{};
    AudioProcessorParameter* parameter {nullptr};
};
