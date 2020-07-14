/*
	==============================================================================
	This file is part of Obxd synthesizer.

	Copyright © 2013-2014 Filatov Vadim
	
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
#include "SynthEngine.h"
#include "ParamsEnum.h"
#include "../JuceLibraryCode/JuceHeader.h"
class MidiMap
{
public:
	int controllers[255];
    int controllers_default[255];
    
    bool loaded = false;
	MidiMap()
	{
        reset();
        set_default();
	}
    void reset(){
        for(int i = 0 ; i < 255;i++){
            controllers[i] = 0;
            controllers_default[i] = 0;
        }
    }
    
    void set_default(){
        int midicc = 71;
        controllers[midicc] = controllers_default[midicc] = VOLUME;
        
        midicc = 15;
        controllers[midicc] = controllers_default[midicc] = VOICE_COUNT;
        
        midicc = 33;
        controllers[midicc] = controllers_default[midicc] = TUNE;
        
        midicc = 17;
        controllers[midicc] = controllers_default[midicc] = OCTAVE;
        
        midicc = 118;
        controllers[midicc] = controllers_default[midicc] = BENDRANGE;
        
        midicc = 34;
        controllers[midicc] = controllers_default[midicc] = BENDOSC2;
        
        midicc = 35;
        controllers[midicc] = controllers_default[midicc] = LEGATOMODE;
        
        midicc = 36;
        controllers[midicc] = controllers_default[midicc] = BENDLFORATE;
        
        midicc = 37;
        controllers[midicc] = controllers_default[midicc] = VFLTENV;
        
        midicc = 120;
        controllers[midicc] = controllers_default[midicc] = VAMPENV;
        
        midicc = 121;
        controllers[midicc] = controllers_default[midicc] = ASPLAYEDALLOCATION;
        
        midicc = 122;
        controllers[midicc] = controllers_default[midicc] = PORTAMENTO;
        
        midicc = 16;
        controllers[midicc] = controllers_default[midicc] = UNISON;
        
        midicc = 123;
        controllers[midicc] = controllers_default[midicc] = UDET;
        
        midicc = 43;
        controllers[midicc] = controllers_default[midicc] = OSC2_DET;
        
        midicc = 19;
        controllers[midicc] = controllers_default[midicc] = LFOFREQ;
        
        midicc = 44;
        controllers[midicc] = controllers_default[midicc] = LFOSINWAVE;
        
        midicc = 45;
        controllers[midicc] = controllers_default[midicc] = LFOSQUAREWAVE;
        
        midicc = 46;
        controllers[midicc] = controllers_default[midicc] = LFOSHWAVE;
        
        midicc = 22;
        controllers[midicc] = controllers_default[midicc] = LFO1AMT;
        
        midicc = 25;
        controllers[midicc] = controllers_default[midicc] = LFO2AMT;
        
        midicc = 47;
        controllers[midicc] = controllers_default[midicc] = LFOOSC1;
        
        midicc = 48;
        controllers[midicc] = controllers_default[midicc] = LFOOSC2;
        
        midicc = 49;
        controllers[midicc] = controllers_default[midicc] = LFOFILTER;
        
        midicc = 50;
        controllers[midicc] = controllers_default[midicc] = LFOPW1;
        
        midicc = 51;
        controllers[midicc] = controllers_default[midicc] = LFOPW2;
        
        midicc = 52;
        controllers[midicc] = controllers_default[midicc] = OSC2HS;
        
        midicc = 53;
        controllers[midicc] = controllers_default[midicc] = XMOD;
        
        midicc = 54;
        controllers[midicc] = controllers_default[midicc] = OSC1P;
        
        midicc = 55;
        controllers[midicc] = controllers_default[midicc] = OSC2P;
        
        midicc = 56;
        controllers[midicc] = controllers_default[midicc] = OSCQuantize;
        
        midicc = 57;
        controllers[midicc] = controllers_default[midicc] = OSC1Saw;
        
        midicc = 58;
        controllers[midicc] = controllers_default[midicc] = OSC1Pul;
        
        midicc = 59;
        controllers[midicc] = controllers_default[midicc] = OSC2Saw;
        
        midicc = 60;
        controllers[midicc] = controllers_default[midicc] = OSC2Pul;
        
        midicc = 61;
        controllers[midicc] = controllers_default[midicc] = PW;
        
        midicc = 62;
        controllers[midicc] = controllers_default[midicc] = BRIGHTNESS;
        
        midicc = 63;
        controllers[midicc] = controllers_default[midicc] = ENVPITCH;
        
        midicc = 100;
        controllers[midicc] = controllers_default[midicc] = OSC1MIX;
        
        midicc = 101;
        controllers[midicc] = controllers_default[midicc] = OSC2MIX;
        
        midicc = 102;
        controllers[midicc] = controllers_default[midicc] = NOISEMIX;
        
        midicc = 103;
        controllers[midicc] = controllers_default[midicc] = FLT_KF;
        
        midicc = 74;
        controllers[midicc] = controllers_default[midicc] = CUTOFF;
        
        midicc = 42;
        controllers[midicc] = controllers_default[midicc] = RESONANCE;
        
        midicc = 104;
        controllers[midicc] = controllers_default[midicc] = MULTIMODE;
        
        midicc = 18;
        controllers[midicc] = controllers_default[midicc] = FILTER_WARM;
        
        midicc = 105;
        controllers[midicc] = controllers_default[midicc] = BANDPASS;
        
        midicc = 106;
        controllers[midicc] = controllers_default[midicc] = FOURPOLE;
        
        midicc = 107;
        controllers[midicc] = controllers_default[midicc] = ENVELOPE_AMT;
        
        midicc = 73;
        controllers[midicc] = controllers_default[midicc] = LATK;
        
        midicc = 36;
        controllers[midicc] = controllers_default[midicc] = LDEC;
        
        midicc = 37;
        controllers[midicc] = controllers_default[midicc] = LSUS;
        
        midicc = 72;
        controllers[midicc] = controllers_default[midicc] = LREL;
        
        midicc = 38;
        controllers[midicc] = controllers_default[midicc] = FATK;
        
        midicc = 39;
        controllers[midicc] = controllers_default[midicc] = FDEC;
        
        midicc = 40;
        controllers[midicc] = controllers_default[midicc] = FSUS;
        
        midicc = 41;
        controllers[midicc] = controllers_default[midicc] = FREL;
        
        midicc = 108;
        controllers[midicc] = controllers_default[midicc] = ENVDER;
        
        midicc = 109;
        controllers[midicc] = controllers_default[midicc] = FILTERDER;
        
        midicc = 110;
        controllers[midicc] = controllers_default[midicc] = PORTADER;
        
        midicc = 81;
        controllers[midicc] = controllers_default[midicc] = PAN1;
        
        midicc = 82;
        controllers[midicc] = controllers_default[midicc] = PAN2;
        
        midicc = 83;
        controllers[midicc] = controllers_default[midicc] = PAN3;
        
        midicc = 84;
        controllers[midicc] = controllers_default[midicc] = PAN4;
        
        midicc = 85;
        controllers[midicc] = controllers_default[midicc] = PAN5;
        
        midicc = 86;
        controllers[midicc] = controllers_default[midicc] = PAN6;
        
        midicc = 87;
        controllers[midicc] = controllers_default[midicc] = PAN7;
        
        midicc = 88;
        controllers[midicc] = controllers_default[midicc] = PAN8;
        
        //midicc = 111;
        //controllers[midicc] = controllers_default[midicc] = ECONOMY_MODE;
        
        //midicc = 112;
        //controllers[midicc] = controllers_default[midicc] = LFO_SYNC;
        
        midicc = 113;
        controllers[midicc] = controllers_default[midicc] = PW_ENV;
        
        midicc = 114;
        controllers[midicc] = controllers_default[midicc] = PW_ENV_BOTH;
        
        midicc = 115;
        controllers[midicc] = controllers_default[midicc] = ENV_PITCH_BOTH;
        
        //midicc = 116;
        //controllers[midicc] = controllers_default[midicc] = FENV_INVERT;
        
        midicc = 117;
        controllers[midicc] = controllers_default[midicc] = PW_OSC2_OFS;
        
        midicc = 118;
        controllers[midicc] = controllers_default[midicc] = LEVEL_DIF;
        
        midicc = 119;
        controllers[midicc] = controllers_default[midicc] = SELF_OSC_PUSH;
        
    }
    
    
    int& operator[](int index)
    {
        if (index >= 255) {
            exit(0);
        }
        return controllers[index];
    }
    
    void setXml( XmlElement &xml){
        for (int i = 0; i < 255; ++i)
        {
            xml.setAttribute("Val_" + String(i), controllers[i]);
        }
    }
    
    void getXml(XmlElement &xml){
        for (int i = 0; i < 255; ++i)
        {
            int tmp = xml.getIntAttribute("Val_" + String(i), controllers_default[i]);
            if (tmp == 0){
                tmp = controllers_default[i];
            }
            
            controllers[i] = tmp;
        }
    }
};
