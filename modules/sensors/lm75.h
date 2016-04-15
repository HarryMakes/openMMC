/*
 *   openMMC -- Open Source modular IPM Controller firmware
 *
 *   Copyright (C) 2015-2016  Henrique Silva <henrique.silva@lnls.br>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>
 */

/*!
 * @file lm75.h
 * @author Henrique Silva <henrique.silva@lnls.br>, LNLS
 * @date September 2015
 *
 * @brief Definitions for LM75 I2C Temperature Sensor
 */

#ifndef LM75_H_
#define LM75_H_

#define LM75_UPDATE_RATE	500

TaskHandle_t vTaskLM75_Handle;

extern const SDR_type_01h_t SDR_LM75_uC;
extern const SDR_type_01h_t SDR_LM75_CLOCK_SWITCH;
extern const SDR_type_01h_t SDR_LM75_DCDC;
extern const SDR_type_01h_t SDR_LM75_RAM;

void LM75_init( void );
void vTaskLM75( void* Parameters );

#endif
