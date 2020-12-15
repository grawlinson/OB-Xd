/*
==============================================================================

This file was auto-generated by the Introjucer!

It contains the basic startup code for a Juce application.

==============================================================================
*/
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <utility>
// #include "GUI/BinaryData.h"

//==============================================================================
ObxdAudioProcessorEditor::ObxdAudioProcessorEditor (ObxdAudioProcessor& ownerFilter)
	: AudioProcessorEditor (&ownerFilter), processor (ownerFilter),
      skinFolder (processor.getSkinFolder()),
      progStart (2000),
      bankStart (1000),
      skinStart (0),
      skins (processor.getSkinFiles()),
      banks (processor.getBankFiles())
{
//    skinFolder = ownerFilter.getCurrentSkinFolder();  // initialized above
    commandManager.registerAllCommandsForTarget(this);
    commandManager.setFirstCommandTarget(this);

    // reset KeyPressMappingSet
    commandManager.getKeyMappings()->resetToDefaultMappings();

    // having set up the default key-mappings, you might now want to load the last set
    // of mappings that the user configured.
    //commandManager.getKeyMappings()->restoreFromXml(lastSavedKeyMappingsXML);

    // Now tell our top-level window to send any keypresses that arrive to the
    // KeyPressMappingSet, which will use them to invoke the appropriate commands.
    //addKeyListener(commandManager.getKeyMappings());
    getTopLevelComponent()->addKeyListener (commandManager.getKeyMappings());
    
    //Timer::callAfterDelay (100, [this] { this->grabKeyboardFocus(); }); // ensure that key presses are sent to the KeyPressTarget object
#if JUCE_WINDOWS
	// No run timer to grab component on  window
#else
	startTimer(100); // This will fix the issue
#endif
    loadSkin (processor);
    repaint();
    
    updateFromHost();
}

void ObxdAudioProcessorEditor::loadSkin (ObxdAudioProcessor& ownerFilter)
{
    knobAttachments.clear();
    buttonListAttachments.clear();
    toggleAttachments.clear();
    imageButtons.clear();
    popupMenus.clear();
    ownerFilter.removeChangeListener (this);
    //File coords("/Users/jimmy/Downloads/coords.xml");
    skinFolder = ownerFilter.getCurrentSkinFolder();
    File coords = skinFolder.getChildFile ("coords.xml");
    bool useClassicSkin = coords.existsAsFile();
    if (!useClassicSkin) {
        addMenuButton (14, 25, 20, ImageCache::getFromMemory(BinaryData::menu_png, BinaryData::menu_pngSize));
        rebuildComponents (processor);
        return;
    }
    
    //if (coords.createInputStream())
    
    XmlDocument skin (coords);
    auto doc = skin.getDocumentElement();
    if (!doc) {
        notLoadSkin = true;
        setSize (1440, 450);
    }
    else {
        
        if (doc->getTagName() == "PROPERTIES"){
            
            forEachXmlChildElementWithTagName(*doc, child, "VALUE"){
                if (child->hasAttribute("NAME") && child->hasAttribute("x") && child->hasAttribute("y")) {
                    String name = child->getStringAttribute("NAME");
                    int x = child->getIntAttribute("x");
                    int y = child->getIntAttribute("y");
                    int d = child->getIntAttribute("d");
                    int w = child->getIntAttribute("w");
                    int h = child->getIntAttribute("h");
                    
                    if (name == "guisize"){ setSize (x, y); }

                    if (name == "resonanceKnob"){ resonanceKnob = addKnob (x, y, d, ownerFilter, RESONANCE, "Resonance", 0); }
                    if (name == "cutoffKnob"){ cutoffKnob = addKnob (x, y, d, ownerFilter, CUTOFF, "Cutoff", 0.4); }
                    if (name == "filterEnvelopeAmtKnob"){ filterEnvelopeAmtKnob = addKnob (x, y, d, ownerFilter, ENVELOPE_AMT, "Envelope", 0); }
                    if (name == "multimodeKnob"){ multimodeKnob = addKnob (x, y, d, ownerFilter, MULTIMODE, "Multimode", 0.5); }
                    
                    if (name == "volumeKnob"){ volumeKnob = addKnob (x, y, d, ownerFilter, VOLUME, "Volume", 0.4); }
                    if (name == "portamentoKnob"){ portamentoKnob = addKnob (x, y, d, ownerFilter, PORTAMENTO, "Portamento", 0); }
                    if (name == "osc1PitchKnob"){ osc1PitchKnob = addKnob (x, y, d, ownerFilter, OSC1P, "Osc1Pitch", 0); }
                    if (name == "pulseWidthKnob"){ pulseWidthKnob = addKnob (x, y, d, ownerFilter, PW, "PW", 0); }
                    if (name == "osc2PitchKnob"){ osc2PitchKnob = addKnob (x, y, d, ownerFilter, OSC2P, "Osc2Pitch", 0); }
                    
                    if (name == "osc1MixKnob"){ osc1MixKnob = addKnob (x, y, d, ownerFilter, OSC1MIX, "Osc1", 1); }
                    if (name == "osc2MixKnob"){ osc2MixKnob = addKnob (x, y, d, ownerFilter, OSC2MIX, "Osc2", 1); }
                    if (name == "noiseMixKnob"){ noiseMixKnob = addKnob (x, y, d, ownerFilter, NOISEMIX, "Noise", 0); }
                    
                    if (name == "xmodKnob"){ xmodKnob = addKnob (x, y, d, ownerFilter, XMOD, "Xmod", 0); }
                    if (name == "osc2DetuneKnob"){ osc2DetuneKnob = addKnob (x, y, d, ownerFilter, OSC2_DET, "Detune", 0); }
                    
                    if (name == "envPitchModKnob"){ envPitchModKnob = addKnob (x, y, d, ownerFilter, ENVPITCH, "PEnv", 0); }
                    if (name == "brightnessKnob"){ brightnessKnob = addKnob (x, y, d, ownerFilter, BRIGHTNESS, "Bri", 1); }
                    
                    if (name == "attackKnob"){ attackKnob = addKnob (x, y, d, ownerFilter, LATK, "Atk", 0); }
                    if (name == "decayKnob"){ decayKnob = addKnob (x, y, d, ownerFilter, LDEC, "Dec", 0); }
                    if (name == "sustainKnob"){ sustainKnob = addKnob (x, y, d, ownerFilter, LSUS, "Sus", 1); }
                    if (name == "releaseKnob"){ releaseKnob = addKnob (x, y, d, ownerFilter, LREL, "Rel", 0); }
                    
                    if (name == "fattackKnob"){ fattackKnob = addKnob (x, y, d, ownerFilter, FATK, "Atk", 0); }
                    if (name == "fdecayKnob"){ fdecayKnob = addKnob (x, y, d, ownerFilter, FDEC, "Dec", 0); }
                    if (name == "fsustainKnob"){ fsustainKnob = addKnob (x, y, d, ownerFilter, FSUS, "Sus", 1); }
                    if (name == "freleaseKnob"){ freleaseKnob = addKnob (x, y, d, ownerFilter, FREL, "Rel", 0); }
                    
                    if (name == "lfoFrequencyKnob"){ lfoFrequencyKnob = addKnob (x, y, d, ownerFilter, LFOFREQ, "Freq", 0); }
                    if (name == "lfoAmt1Knob"){ lfoAmt1Knob = addKnob (x, y, d, ownerFilter, LFO1AMT, "Pitch", 0); }
                    if (name == "lfoAmt2Knob"){ lfoAmt2Knob = addKnob (x, y, d, ownerFilter, LFO2AMT, "PWM", 0); }
                    
                    if (name == "lfoSinButton"){ lfoSinButton = addButton (x, y, w, h, ownerFilter, LFOSINWAVE, "Sin"); }
                    if (name == "lfoSquareButton"){ lfoSquareButton = addButton (x, y,  w, h, ownerFilter, LFOSQUAREWAVE, "SQ"); }
                    if (name == "lfoSHButton"){ lfoSHButton = addButton (x, y,  w, h, ownerFilter, LFOSHWAVE, "S&H"); }
                    
                    if (name == "lfoOsc1Button"){ lfoOsc1Button = addButton (x, y,  w, h, ownerFilter, LFOOSC1, "Osc1"); }
                    if (name == "lfoOsc2Button"){ lfoOsc2Button = addButton (x, y,  w, h, ownerFilter, LFOOSC2, "Osc2"); }
                    if (name == "lfoFilterButton"){ lfoFilterButton = addButton (x, y,  w, h, ownerFilter, LFOFILTER, "Filt"); }
                    
                    if (name == "lfoPwm1Button"){ lfoPwm1Button = addButton (x, y,  w, h, ownerFilter, LFOPW1, "Osc1"); }
                    if (name == "lfoPwm2Button"){ lfoPwm2Button = addButton (x, y,  w, h, ownerFilter, LFOPW2, "Osc2"); }
                    
                    if (name == "hardSyncButton"){ hardSyncButton = addButton (x, y,  w, h, ownerFilter, OSC2HS, "Sync"); }
                    if (name == "osc1SawButton"){ osc1SawButton = addButton (x, y,  w, h, ownerFilter, OSC1Saw, "S"); }
                    if (name == "osc2SawButton"){ osc2SawButton = addButton (x, y,  w, h, ownerFilter, OSC2Saw, "S"); }
                    
                    if (name == "osc1PulButton"){ osc1PulButton = addButton (x, y,  w, h, ownerFilter, OSC1Pul, "P"); }
                    if (name == "osc2PulButton"){ osc2PulButton = addButton (x, y,  w, h, ownerFilter, OSC2Pul, "P"); }
                    
                    if (name == "pitchQuantButton"){ pitchQuantButton =  addButton (x, y,  w, h, ownerFilter, OSCQuantize, "Step"); }
                    
                    if (name == "filterBPBlendButton"){ filterBPBlendButton = addButton (x, y,  w, h, ownerFilter, BANDPASS, "Bp"); }
                    if (name == "fourPoleButton"){ fourPoleButton = addButton (x, y,  w, h, ownerFilter, FOURPOLE, "24"); }
                    if (name == "filterHQButton"){ filterHQButton = addButton (x, y,  w, h, ownerFilter, FILTER_WARM, "HQ"); }
                    
                    if (name == "filterKeyFollowButton"){ filterKeyFollowButton =  addButton (x, y,  w, h, ownerFilter, FLT_KF, "Key"); }
                    if (name == "unisonButton"){ unisonButton = addButton (x, y,  w, h, ownerFilter, UNISON, "Uni"); }
                    
                    if (name == "tuneKnob"){ tuneKnob = addKnob (x, y, d, ownerFilter, TUNE, "Tune", 0.5); }
                    if (name == "transposeKnob"){ transposeKnob = addKnob (x, y, d, ownerFilter, OCTAVE, "Transpose", 0.5); }
                    
                    if (name == "voiceDetuneKnob"){ voiceDetuneKnob =addKnob (x, y, d, ownerFilter, UDET, "VoiceDet", 0); }
                    
                    if (name == "bendLfoRateKnob"){ bendLfoRateKnob = addKnob (x, y, d, ownerFilter, BENDLFORATE, "ModRate", 0.4); }
                    if (name == "veloFltEnvKnob"){ veloFltEnvKnob = addKnob (x, y, d, ownerFilter, VFLTENV, "VFE", 0); }
                    if (name == "veloAmpEnvKnob"){ veloAmpEnvKnob = addKnob (x, y, d, ownerFilter, VAMPENV, "VAE", 0); }
                    if (name == "midiLearnButton"){ midiLearnButton = addButton (x, y,  w, h, ownerFilter, MIDILEARN, "LEA"); }
                    if (name == "midiUnlearnButton"){ midiUnlearnButton = addButton (x, y,  w, h, ownerFilter, UNLEARN, "UNL"); }
                    
                    if (name == "pan1Knob"){ pan1Knob = addKnob (x, y, d, ownerFilter, PAN1, "1", 0.5); }
                    if (name == "pan2Knob"){ pan2Knob = addKnob (x, y, d, ownerFilter, PAN2, "2", 0.5); }
                    if (name == "pan3Knob"){ pan3Knob = addKnob (x, y, d, ownerFilter, PAN3, "3", 0.5); }
                    if (name == "pan4Knob"){ pan4Knob = addKnob (x, y, d, ownerFilter, PAN4, "4", 0.5); }
                    
                    if (name == "pan5Knob"){ pan5Knob = addKnob (x, y, d, ownerFilter, PAN5, "5", 0.5); }
                    if (name == "pan6Knob"){ pan6Knob = addKnob (x, y, d, ownerFilter, PAN6, "6", 0.5); }
                    if (name == "pan7Knob"){ pan7Knob = addKnob (x, y, d, ownerFilter, PAN7, "7", 0.5); }
                    if (name == "pan8Knob"){ pan8Knob = addKnob (x, y, d, ownerFilter, PAN8, "8", 0.5); }
                    
                    if (name == "bendOsc2OnlyButton"){ bendOsc2OnlyButton = addButton (x, y,  w, h, ownerFilter, BENDOSC2, "Osc2"); }
                    if (name == "bendRangeButton"){ bendRangeButton = addButton (x, y,  w, h, ownerFilter, BENDRANGE, "12"); }
                    if (name == "asPlayedAllocButton"){ asPlayedAllocButton = addButton (x, y,  w, h, ownerFilter, ASPLAYEDALLOCATION, "APA"); }
                    
                    if (name == "filterDetuneKnob"){ filterDetuneKnob = addKnob (x, y, d, ownerFilter, FILTERDER, "Flt", 0.2); }
                    if (name == "portamentoDetuneKnob"){ portamentoDetuneKnob = addKnob (x, y, d, ownerFilter, PORTADER, "Port", 0.2); }
                    if (name == "envelopeDetuneKnob"){ envelopeDetuneKnob = addKnob (x, y, d, ownerFilter, ENVDER, "Env", 0.2); }
                                        
                    if (name == "voiceSwitch"){
                        //if (voiceSwitch) voiceSwitch->setVisible(false);
#if JUCE_WINDOWS || JUCE_LINUX
                        voiceSwitch = addList (x, y, w, h, ownerFilter, VOICE_COUNT, "VoiceCount", ImageCache::getFromFile(skinFolder.getChildFile("voices.png"))); }
#else
                        voiceSwitch = addList (x, y, w, h, ownerFilter, VOICE_COUNT, "VoiceCount", ImageCache::getFromFile(skinFolder.getChildFile("voices@2x.png"))); }
#endif

                    if (name == "legatoSwitch"){
                        //if (legatoSwitch) legatoSwitch->setVisible(false);
#if JUCE_WINDOWS || JUCE_LINUX
                        legatoSwitch = addList (x, y, w, h, ownerFilter, LEGATOMODE, "Legato", ImageCache::getFromFile(skinFolder.getChildFile("legato.png"))); }
#else
                        legatoSwitch = addList (x, y, w, h, ownerFilter, LEGATOMODE, "Legato", ImageCache::getFromFile(skinFolder.getChildFile("legato@2x.png"))); }
#endif

                    
                    if (name == "menu")
                    {
                        addMenuButton (x, y, d,
#if JUCE_WINDOWS || JUCE_LINUX
                                 ImageCache::getFromFile (skinFolder.getChildFile ("menu.png")));
#else
                                 ImageCache::getFromFile (skinFolder.getChildFile ("menu@2x.png")));
#endif
                    }
                    
                    //DBG(" Name: " << name << " X: " <<x <<" Y: "<<y);
                }
            }
        }
    }
    
    // Prepare data
    if (voiceSwitch)
    {
        for (int i = 1; i <= 32; ++i)
        {
            voiceSwitch->addChoice (String (i));
        }
        
        auto voiceOption = ownerFilter.getPluginState().getParameter (ownerFilter.getEngineParameterId (VOICE_COUNT))->getValue();
        voiceSwitch->setValue (voiceOption, dontSendNotification);
    }
    
    if (legatoSwitch)
    {
        legatoSwitch->addChoice ("Keep All");
        legatoSwitch->addChoice ("Keep Filter Envelope");
        legatoSwitch->addChoice ("Keep Amplitude Envelope");
        legatoSwitch->addChoice ("Retrig");
        auto legatoOption = ownerFilter.getPluginState().getParameter (ownerFilter.getEngineParameterId (LEGATOMODE))->getValue();
        legatoSwitch->setValue (legatoOption, dontSendNotification);
    }
    
    createMenu();
    ownerFilter.addChangeListener (this);
    repaint();
}
ObxdAudioProcessorEditor::~ObxdAudioProcessorEditor()
{
	processor.removeChangeListener (this);
//    deleteAllChildren();  // WATCH OUT!
}

void ObxdAudioProcessorEditor::placeLabel (int x, int y, String text)
{
	Label* lab = new Label();
	lab->setBounds (x, y, 110, 20);
	lab->setJustificationType (Justification::centred);
	lab->setText (text,dontSendNotification);
    lab->setInterceptsMouseClicks (false, true);
	addAndMakeVisible (lab);
}

ButtonList* ObxdAudioProcessorEditor::addList (int x, int y, int width, int height, ObxdAudioProcessor& filter, int parameter, String /*name*/, Image img)
{
    #if JUCE_WINDOWS || JUCE_LINUX
    ButtonList *bl = new ButtonList (img, height);
    #else
    ButtonList *bl = new ButtonList (img, height*2);
    #endif

    buttonListAttachments.add (new ButtonList::ButtonListAttachment (filter.getPluginState(),
                                                                     filter.getEngineParameterId (parameter),
                                                                     *bl));
    
	bl->setBounds (x, y, width, height);
	addAndMakeVisible (bl);
    
	return bl;

}

Knob* ObxdAudioProcessorEditor::addKnob (int x, int y, int d, ObxdAudioProcessor& filter, int parameter, String /*name*/, float defval)
{
#if JUCE_WINDOWS || JUCE_LINUX
    Knob* knob = new Knob (ImageCache::getFromFile(skinFolder.getChildFile("knob.png")), 48);
#else
    Knob* knob = new Knob (ImageCache::getFromFile(skinFolder.getChildFile("knob@2x.png")), 96);
#endif

    knobAttachments.add (new Knob::KnobAttachment (filter.getPluginState(),
                                                   filter.getEngineParameterId (parameter),
                                                   *knob));
    
	knob->setSliderStyle (Slider::RotaryVerticalDrag);
	knob->setTextBoxStyle (knob->NoTextBox, true, 0, 0);
	knob->setRange (0, 1);
	knob->setBounds (x, y, d+(d/6), d+(d/6));
	knob->setTextBoxIsEditable (false);
	knob->setDoubleClickReturnValue (true, defval);
    knob->setValue (filter.getPluginState().getParameter (filter.getEngineParameterId (parameter))->getValue());
    addAndMakeVisible (knob);
    
	return knob;
}


void ObxdAudioProcessorEditor::clean()
{
    this->removeAllChildren();
}

TooglableButton* ObxdAudioProcessorEditor::addButton (int x, int y, int w, int h, ObxdAudioProcessor& filter, int parameter, String name)
{
#if JUCE_WINDOWS || JUCE_LINUX
    TooglableButton* button = new TooglableButton (ImageCache::getFromFile(skinFolder.getChildFile("button.png")));
#else
    TooglableButton* button = new TooglableButton (ImageCache::getFromFile(skinFolder.getChildFile("button@2x.png")));
#endif
    if (parameter != UNLEARN){
        toggleAttachments.add (new AudioProcessorValueTreeState::ButtonAttachment (filter.getPluginState(),
                                                                      filter.getEngineParameterId (parameter),
                                                                      *button));
    } else {
        button->addListener(this);
    }
	button->setBounds (x, y, w, h);
	button->setButtonText (name);
    button->setToggleState(filter.getPluginState().getParameter (filter.getEngineParameterId (parameter))->getValue(),
                      dontSendNotification);
    
    addAndMakeVisible (button);
    
	return button;
}

void ObxdAudioProcessorEditor::addMenuButton (int x, int y, int d, const Image& image)
{
    ImageButton* imageButton;
    imageButtons.add (imageButton = new ImageButton());
    imageButton->setBounds (x, y, d, d);
    imageButton->setImages (false,
                            true,
                            true,
                            image,
                            1.0f, // menu transparency
                            Colour(),
                            image,
                            1.0f, // menu hover transparency
                            Colour(),
                            image,
                            0.3f, // menu click transparency
                            Colour());
    
    //imageButton->addListener (this);
    imageButton->onClick = [this](){
        ImageButton *imageButton = this->imageButtons[0];
        auto x   = imageButton->getScreenX();
        auto y   = imageButton->getScreenY();
        auto dx  = imageButton->getWidth();
        auto pos = Point<int> (x, y + dx);
        resultFromMenu (pos);
    };
    addAndMakeVisible (imageButton);
}

void ObxdAudioProcessorEditor::rebuildComponents (ObxdAudioProcessor& ownerFilter)
{
	skinFolder = ownerFilter.getCurrentSkinFolder();

	ownerFilter.removeChangeListener (this);

    // deleteAllChildren();  // WATCH OUT!

		setSize (1440, 450);

	ownerFilter.addChangeListener (this);
	repaint();
}

void ObxdAudioProcessorEditor::createMenu ()
{
    PopupMenu* menu = new PopupMenu();
    PopupMenu progMenu;
    PopupMenu bankMenu;
    PopupMenu skinMenu;

    skins = processor.getSkinFiles();
    banks = processor.getBankFiles();
    
    {
        for (int i = 0; i < processor.getNumPrograms(); ++i)
        {
            progMenu.addItem (i + progStart + 1,
                              processor.getProgramName (i),
                              true,
                              i == processor.getCurrentProgram());
        }
        
        menu->addSubMenu("Programs", progMenu);
    }
    
    {
        const String currentBank = processor.getCurrentBankFile().getFileName();
        
        for (int i = 0; i < banks.size(); ++i)
        {
            const File bank = banks.getUnchecked (i);
            bankMenu.addItem (i + bankStart + 1,
                              bank.getFileNameWithoutExtension(),
                              true,
                              bank.getFileName() == currentBank);
        }
        
        menu->addSubMenu ("Banks", bankMenu);
    }
    
    {
        for (int i = 0; i < skins.size(); ++i)
        {
            const File skin = skins.getUnchecked (i);
            skinMenu.addItem (i + skinStart + 1,
                              skin.getFileName(),
                              true,
                              skin.getFileName() == skinFolder.getFileName());
        }
        
        menu->addSubMenu ("Themes", skinMenu);
        // About // menu.addItem(1, String("Release ") +  String(JucePlugin_VersionString).dropLastCharacters(2), false);
    }
    
    popupMenus.add (menu);
}

void ObxdAudioProcessorEditor::resultFromMenu (const Point<int> pos)
{
    int result = popupMenus[0]->showAt (Rectangle<int> (pos.getX(), pos.getY(), 1, 1));
    
    if (result >= (skinStart + 1) && result <= (skinStart + skins.size()))
    {
        result -= 1;
        result -= skinStart;
        
        const File newSkinFolder = skins.getUnchecked (result);
        processor.setCurrentSkinFolder (newSkinFolder.getFileName());
        
        //rebuildComponents (processor);
        clean();
        loadSkin (processor);
    }
    else if (result >= (bankStart + 1) && result <= (bankStart + banks.size()))
    {
        result -= 1;
        result -= bankStart;
        
        const File bankFile = banks.getUnchecked (result);
        processor.loadFromFXBFile (bankFile);
        clean();
        loadSkin (processor);
    }
    else if (result >= (progStart + 1) && result <= (progStart + processor.getNumPrograms()))
    {
        result -= 1;
        result -= progStart;
        processor.setCurrentProgram (result);
        clean();
        loadSkin (processor);
    }
}

void ObxdAudioProcessorEditor::nextProgram() {
    int cur = processor.getCurrentProgram() +  1;
    if (cur == processor.getNumPrograms()) {
        cur = 0;
    }
    processor.setCurrentProgram (cur);
    clean();
    loadSkin (processor);
}
void ObxdAudioProcessorEditor::prevProgram() {
    int cur = processor.getCurrentProgram() -  1;
    if (cur < 0) {
        cur = processor.getNumPrograms() - 1;
    }
    processor.setCurrentProgram (cur);
    clean();
    loadSkin (processor);
}
void ObxdAudioProcessorEditor::buttonClicked (Button* b)
{
    /*
    auto imageButton = dynamic_cast<ImageButton*> (b);
    
    if (imageButton == imageButtons[0])
    {
        auto x   = imageButton->getScreenX();
        auto y   = imageButton->getScreenY();
        auto dx  = imageButton->getWidth();
        auto pos = Point<int> (x, y + dx);

        resultFromMenu (pos);
    }*/
    
    
    auto toggleButton = dynamic_cast<TooglableButton*> (b);
    if (toggleButton == midiUnlearnButton){
        if (midiUnlearnButton->getToggleState()){
            processor.getMidiMap().reset();
            processor.getMidiMap().set_default();
            processor.sendChangeMessage();
        }
    }
    
}

//==============================================================================

void ObxdAudioProcessorEditor::updateFromHost() {
    for (int i = 0; i < knobAttachments.size(); ++i)
    {
        knobAttachments[i]->updateToSlider();
    }
    /*
    for (int i = 0; i < toggleAttachments.size(); ++i)
    {
        toggleAttachments[i]->updateToSlider();
    }*/
    
    for (int i = 0; i < buttonListAttachments.size(); ++i)
    {
        buttonListAttachments[i]->updateToSlider();
    }
    
    // Set to unlearn to false
    if ( midiUnlearnButton && midiUnlearnButton->getToggleState()) {
        midiUnlearnButton->setToggleState(false, NotificationType:: sendNotification);
    }
    
    repaint();
}
void ObxdAudioProcessorEditor::changeListenerCallback (ChangeBroadcaster* source)
{
    updateFromHost();
}

void ObxdAudioProcessorEditor::mouseUp (const MouseEvent& e)
{
	if (e.mods.isRightButtonDown() || e.mods.isCommandDown())
	{
        resultFromMenu (e.getMouseDownScreenPosition());
	}
}

void ObxdAudioProcessorEditor::paint(Graphics& g)
{
	g.fillAll (Colours::black);
#if JUCE_WINDOWS || JUCE_LINUX
	const File mainFile(skinFolder.getChildFile("main.png"));
#else
    const File mainFile(skinFolder.getChildFile("main@2x.png"));
#endif
    
    if (!notLoadSkin && skinFolder.exists() && mainFile.exists())
	{
        
        const Image image = ImageCache::getFromFile(mainFile);
        
#if JUCE_WINDOWS || JUCE_LINUX
        g.drawImage (image,
                     0, 0, image.getWidth(), image.getHeight(),
                     0, 0, image.getWidth(), image.getHeight());
#else
        g.drawImage (image,
                     0, 0, image.getWidth()/2, image.getHeight()/2,
                     0, 0, image.getWidth(), image.getHeight());
#endif

	}
	else
	{
		const Image image = ImageCache::getFromMemory(BinaryData::main_png, BinaryData::main_pngSize);
        
        // g.setImageResamplingQuality(Graphics::ResamplingQuality::highResamplingQuality);
        
		g.drawImage (image,
					 0, 0, image.getWidth(), image.getHeight(),
					 0, 0, image.getWidth(), image.getHeight());
	}

}

/*
bool ObxdAudioProcessorEditor::keyPressed(const KeyPress & press) {
    if (press.getKeyCode() == '+' || press.getKeyCode() == KeyPress::numberPadAdd)
    {
        nextProgram();
        return false; // r+eturn true when the keypress was handled
    }
    if (press.getKeyCode() == '-' || press.getKeyCode() == KeyPress::numberPadSubtract)
    {
        prevProgram();
        return false; // return true when the keypress was handled
    }
    
    return false; // return false if you don't handle the keypress
}*/
