/* Copyright 2023 Dual Tachyon
 * https://github.com/DualTachyon
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 */

#if defined(ENABLE_FMRADIO)
#include "app/fm.h"
#endif
#include "audio.h"
#include "bsp/dp32g030/gpio.h"
#if defined(ENABLE_FMRADIO)
#include "driver/bk1080.h"
#endif
#include "driver/bk4819.h"
#include "driver/gpio.h"
#include "driver/system.h"
#include "driver/systick.h"
#include "functions.h"
#include "misc.h"
#include "settings.h"
#include "ui/ui.h"

VOICE_ID_t gVoiceID[8];
uint8_t gVoiceReadIndex;
uint8_t gVoiceWriteIndex;
volatile uint16_t gCountdownToPlayNextVoice;
volatile bool gFlagPlayQueuedVoice;
VOICE_ID_t gAnotherVoiceID = VOICE_ID_INVALID;
BEEP_Type_t gBeepToPlay;

void AUDIO_PlayBeep(BEEP_Type_t Beep)
{
	uint16_t ToneConfig;
	uint16_t ToneFrequency;
	uint16_t Duration;

	if (Beep != BEEP_500HZ_60MS_DOUBLE_BEEP && Beep != BEEP_440HZ_500MS && !gEeprom.BEEP_CONTROL) {
		return;
	}

#if defined(ENABLE_AIRCOPY)
	if (gScreenToDisplay == DISPLAY_AIRCOPY) {
		return;
	}
#endif
	if (gCurrentFunction == FUNCTION_RECEIVE) {
		return;
	}
	if (gCurrentFunction == FUNCTION_MONITOR) {
		return;
	}

	ToneConfig = BK4819_ReadRegister(BK4819_REG_71);

	GPIO_ClearBit(&GPIOC->DATA, GPIOC_PIN_AUDIO_PATH);

	if (gCurrentFunction == FUNCTION_POWER_SAVE && gRxIdleMode) {
		BK4819_RX_TurnOn();
	}

#if defined(ENABLE_FMRADIO)
	if (gFmRadioMode) {
		BK1080_Mute(true);
	}
#endif
	SYSTEM_DelayMs(20);
	switch (Beep) {
	case BEEP_1KHZ_60MS_OPTIONAL:
		ToneFrequency = 1000;
		break;
	case BEEP_500HZ_60MS_DOUBLE_BEEP_OPTIONAL:
	case BEEP_500HZ_60MS_DOUBLE_BEEP:
		ToneFrequency = 500;
		break;
	default:
		ToneFrequency = 440;
		break;
	}
	BK4819_PlayTone(ToneFrequency, true);
	SYSTEM_DelayMs(2);
	GPIO_SetBit(&GPIOC->DATA, GPIOC_PIN_AUDIO_PATH);
	SYSTEM_DelayMs(60);

	switch (Beep) {
	case BEEP_500HZ_60MS_DOUBLE_BEEP_OPTIONAL:
	case BEEP_500HZ_60MS_DOUBLE_BEEP:
		BK4819_ExitTxMute();
		SYSTEM_DelayMs(60);
		BK4819_EnterTxMute();
		SYSTEM_DelayMs(20);
		// Fallthrough
	case BEEP_1KHZ_60MS_OPTIONAL:
		BK4819_ExitTxMute();
		Duration = 60;
		break;
	case BEEP_440HZ_500MS:
	default:
		BK4819_ExitTxMute();
		Duration = 500;
		break;
	}

	SYSTEM_DelayMs(Duration);
	BK4819_EnterTxMute();
	SYSTEM_DelayMs(20);
	GPIO_ClearBit(&GPIOC->DATA, GPIOC_PIN_AUDIO_PATH);

	gVoxResumeCountdown = 80;

	SYSTEM_DelayMs(5);
	BK4819_TurnsOffTones_TurnsOnRX();
	SYSTEM_DelayMs(5);
	BK4819_WriteRegister(BK4819_REG_71, ToneConfig);
	if (gEnableSpeaker) {
		GPIO_SetBit(&GPIOC->DATA, GPIOC_PIN_AUDIO_PATH);
	}
#if defined(ENABLE_FMRADIO)
	if (gFmRadioMode) {
		BK1080_Mute(false);
	}
#endif
	if (gCurrentFunction == FUNCTION_POWER_SAVE && gRxIdleMode) {
		BK4819_Sleep();
	}
}

void AUDIO_PlayVoice(uint8_t VoiceID)
{
	return;
}

void AUDIO_PlaySingleVoice(bool bFlag)
{
	return;
}

void AUDIO_SetVoiceID(uint8_t Index, VOICE_ID_t VoiceID)
{
	return;
}

uint8_t AUDIO_SetDigitVoice(uint8_t Index, uint16_t Value)
{
	return 0;
}

void AUDIO_PlayQueuedVoice(void)
{
	return;
}

