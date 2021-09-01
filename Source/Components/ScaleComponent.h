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
