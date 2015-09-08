/************************************************************************************
 * configs/sama5d2-xult/src/sama5d2-xult.h
 *
 *   Copyright (C) 2015 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ************************************************************************************/

#ifndef __CONFIGS_SAMA5D2_XULT_SRC_SAMA5D2_XULT_H
#define __CONFIGS_SAMA5D2_XULT_SRC_SAMA5D2_XULT_H

/************************************************************************************
 * Included Files
 ************************************************************************************/

#include <nuttx/config.h>
#include <nuttx/compiler.h>

#include <stdint.h>
#include <stdbool.h>

#include <arch/irq.h>
#include <nuttx/irq.h>

#include "chip/sam_pinmap.h"

/************************************************************************************
 * Pre-processor Definitions
 ************************************************************************************/
/* Configuration ************************************************************/

/* LEDs *****************************************************************************/
/* There are 3 LEDs on the SAMA5D4-EK:
 *
 * ------------------------------ ------------------- -------------------------
 * SAMA5D4 PIO                    SIGNAL              USAGE
 * ------------------------------ ------------------- -------------------------
 * PE28/NWAIT/RTS4/A19            1Wire_PE28          1-WIRE ROM, LCD, D8 (green)
 * PE8/A8/TCLK3/PWML3             LED_USER_PE8        LED_USER (D10)
 * PE9/A9/TIOA2                   LED_POWER_PE9       LED_POWER (D9, Red)
 * ------------------------------ ------------------- -------------------------
 *
 * - D8: D8 is shared with other functions and cannot be used if the 1-Wire ROM
 *   is used.  I am not sure of the LCD function, but the LED may not be available
 *   if the LCD is used either.  We will avoid using D8 just for simplicity.
 * - D10:  Nothing special here.  A low output illuminates.
 * - D9: The Power ON LED.  Connects to the via an IRLML2502 MOSFET.  This LED will
 *   be on when power is applied but otherwise; a low output value will turn it
 *   off.
 */

#define PIO_LED_GREEN (PIO_OUTPUT | PIO_CFG_PULLUP | PIO_OUTPUT_SET | \
                       PIO_PORT_PIOE | PIO_PIN8)
#define PIO_LED_BLUE  (PIO_OUTPUT | PIO_CFG_PULLUP | PIO_OUTPUT_CLEAR | \
                       PIO_PORT_PIOE | PIO_PIN9)

/* Buttons **************************************************************************/
/* A single button, PB_USER (PB6), is available on the SAMA5D2-XULT
 *
 *  ------------------------------ ------------------- -------------------------
 *  SAMA5D2 PIO                    SIGNAL              USAGE
 *  ------------------------------ ------------------- -------------------------
 *  PB6                            USER_PB_PB6         PB_USER push button
 *  ------------------------------ ------------------- -------------------------
 *
 *  Closing PB_USER will bring PB6 to ground so 1) PB6 should have a weak pull-up,
 *  and 2) when PB_USER is pressed, a low value will be senses.
 */

#define PIO_BTN_USER (PIO_INPUT | PIO_CFG_PULLUP | PIO_CFG_DEGLITCH | \
                      PIO_INT_BOTHEDGES | PIO_PORT_PIOB | PIO_PIN6)
#define IRQ_BTN_USER  SAM_IRQ_PB6


/************************************************************************************
 * Public Types
 ************************************************************************************/

/************************************************************************************
 * Public data
 ************************************************************************************/

#ifndef __ASSEMBLY__

/************************************************************************************
 * Public Functions
 ************************************************************************************/

/****************************************************************************
 * Name: sam_bringup
 *
 * Description:
 *   Bring up board features
 *
 ****************************************************************************/

int sam_bringup(void);

#endif /* __ASSEMBLY__ */
#endif /* __CONFIGS_SAMA5D2_XULT_SRC_SAMA5D2_XULT_H */
