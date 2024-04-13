/*
*	File:		ConsoleXBuss.h
*	
*	Version:	1.0
* 
*	Created:	2/23/24
*	
*	Copyright:  Copyright � 2024 Airwindows, Airwindows uses the MIT license
* 
*	Disclaimer:	IMPORTANT:  This Apple software is supplied to you by Apple Computer, Inc. ("Apple") in 
*				consideration of your agreement to the following terms, and your use, installation, modification 
*				or redistribution of this Apple software constitutes acceptance of these terms.  If you do 
*				not agree with these terms, please do not use, install, modify or redistribute this Apple 
*				software.
*
*				In consideration of your agreement to abide by the following terms, and subject to these terms, 
*				Apple grants you a personal, non-exclusive license, under Apple's copyrights in this 
*				original Apple software (the "Apple Software"), to use, reproduce, modify and redistribute the 
*				Apple Software, with or without modifications, in source and/or binary forms; provided that if you 
*				redistribute the Apple Software in its entirety and without modifications, you must retain this 
*				notice and the following text and disclaimers in all such redistributions of the Apple Software. 
*				Neither the name, trademarks, service marks or logos of Apple Computer, Inc. may be used to 
*				endorse or promote products derived from the Apple Software without specific prior written 
*				permission from Apple.  Except as expressly stated in this notice, no other rights or 
*				licenses, express or implied, are granted by Apple herein, including but not limited to any 
*				patent rights that may be infringed by your derivative works or by other works in which the 
*				Apple Software may be incorporated.
*
*				The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO WARRANTIES, EXPRESS OR 
*				IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY 
*				AND FITNESS FOR A PARTICULAR PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE 
*				OR IN COMBINATION WITH YOUR PRODUCTS.
*
*				IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR CONSEQUENTIAL 
*				DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
*				OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, 
*				REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER 
*				UNDER THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN 
*				IF APPLE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/
#include "AUEffectBase.h"
#include "ConsoleXBussVersion.h"

#if AU_DEBUG_DISPATCHER
	#include "AUDebugDispatcher.h"
#endif


#ifndef __ConsoleXBuss_h__
#define __ConsoleXBuss_h__


#pragma mark ____ConsoleXBuss Parameters

// parameters
static const float kDefaultValue_ParamOne = 0.5;
static const float kDefaultValue_ParamTwo = 0.5;
static const float kDefaultValue_ParamThree = 0.5;
static const float kDefaultValue_ParamFour = 0.5;
static const float kDefaultValue_ParamFive = 0.5;
static const float kDefaultValue_ParamSix = 100.0;
static const float kDefaultValue_ParamSeven = 0.5;
static const float kDefaultValue_ParamEight = 0.5;

static CFStringRef kParameterOneName = CFSTR("Air");
static CFStringRef kParameterTwoName = CFSTR("Fire");
static CFStringRef kParameterThreeName = CFSTR("Stone");
static CFStringRef kParameterFourName = CFSTR("Reso");
static CFStringRef kParameterFiveName = CFSTR("Range");
static CFStringRef kParameterSixName = CFSTR("Top dB");
static CFStringRef kParameterSevenName = CFSTR("Pan");
static CFStringRef kParameterEightName = CFSTR("Fader");
//Alter the name if desired, but using the plugin name is a start

enum {
	kParam_One =0,
	kParam_Two =1,
	kParam_Three =2,
	kParam_Four =3,
	kParam_Five =4,
	kParam_Six =5,
	kParam_Seven =6,
	kParam_Eight =7,
	//Add your parameters here...
	kNumberOfParameters=8
};
const int dscBuf = 90;


#pragma mark ____ConsoleXBuss
class ConsoleXBuss : public AUEffectBase
{
public:
	ConsoleXBuss(AudioUnit component);
#if AU_DEBUG_DISPATCHER
	virtual ~ConsoleXBuss () { delete mDebugDispatcher; }
#endif
	
	virtual ComponentResult Reset(AudioUnitScope inScope, AudioUnitElement inElement);

	virtual OSStatus ProcessBufferLists(AudioUnitRenderActionFlags & ioActionFlags, 
						const AudioBufferList & inBuffer, AudioBufferList & outBuffer, 
						UInt32 inFramesToProcess);
	virtual UInt32 SupportedNumChannels(const AUChannelInfo ** outInfo);

	virtual	ComponentResult		GetParameterValueStrings(AudioUnitScope			inScope,
														 AudioUnitParameterID		inParameterID,
														 CFArrayRef *			outStrings);
    
	virtual	ComponentResult		GetParameterInfo(AudioUnitScope			inScope,
												 AudioUnitParameterID	inParameterID,
												 AudioUnitParameterInfo	&outParameterInfo);
    
	virtual ComponentResult		GetPropertyInfo(AudioUnitPropertyID		inID,
												AudioUnitScope			inScope,
												AudioUnitElement		inElement,
												UInt32 &			outDataSize,
												Boolean	&			outWritable );
	
	virtual ComponentResult		GetProperty(AudioUnitPropertyID inID,
											AudioUnitScope 		inScope,
											AudioUnitElement 		inElement,
											void *			outData);

	virtual ComponentResult    Initialize();
	virtual bool				SupportsTail () { return true; }
    virtual Float64				GetTailTime() {return (1.0/GetSampleRate())*0.0;} //in SECONDS! gsr * a number = in samples
    virtual Float64				GetLatency() {return (1.0/GetSampleRate())*0.0;}	// in SECONDS! gsr * a number = in samples
	
	/*! @method Version */
	virtual ComponentResult		Version() { return kConsoleXBussVersion; }
	
		private: 
	enum {
		biq_freq,
		biq_reso,
		biq_a0,
		biq_a1,
		biq_a2,
		biq_b1,
		biq_b2,
		biq_sL1,
		biq_sL2,
		biq_sR1,
		biq_sR2,
		biq_total
	};
	double biquad[biq_total];
	
	enum {
		pvAL1,
		pvSL1,
		accSL1,
		acc2SL1,
		pvAL2,
		pvSL2,
		accSL2,
		acc2SL2,
		pvAL3,
		pvSL3,
		accSL3,
		pvAL4,
		pvSL4,
		gndavgL,
		outAL,
		gainAL,
		pvAR1,
		pvSR1,
		accSR1,
		acc2SR1,
		pvAR2,
		pvSR2,
		accSR2,
		acc2SR2,
		pvAR3,
		pvSR3,
		accSR3,
		pvAR4,
		pvSR4,
		gndavgR,
		outAR,
		gainAR,
		air_total
	};
	double air[air_total];
	
	enum {
		prevSampL1,
		prevSlewL1,
		accSlewL1,
		prevSampL2,
		prevSlewL2,
		accSlewL2,
		prevSampL3,
		prevSlewL3,
		accSlewL3,
		kalGainL,
		kalOutL,
		prevSampR1,
		prevSlewR1,
		accSlewR1,
		prevSampR2,
		prevSlewR2,
		accSlewR2,
		prevSampR3,
		prevSlewR3,
		accSlewR3,
		kalGainR,
		kalOutR,
		kal_total
	};
	double kal[kal_total];
	
	double mpkL[2005];
	double mpkR[2005];
	double f[66];
	double prevfreqMPeak;
	double prevamountMPeak;
	int mpc;
	
	double dBaL[dscBuf+5];
	double dBaR[dscBuf+5];
	double dBaPosL;
	double dBaPosR;
	int dBaXL;
	int dBaXR;
	
	double trebleGainA;
	double trebleGainB;
	double midGainA;
	double midGainB;
	double mPeakA;
	double mPeakB;
	double bassGainA;
	double bassGainB;
	double panA;
	double panB;
	double inTrimA;
	double inTrimB;
	
	uint32_t fpdL;
	uint32_t fpdR;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#endif