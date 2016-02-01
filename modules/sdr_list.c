#include "sdr.h"
#include "fpga_spi.h"
#include "sensors.h"

#define STR(x) _STR(x)
#define _STR(x) #x
#define STR_SIZE(x) (sizeof(x) -1)

/* Management Controller Device Locator Record 37.9 SDR Type 12h */
const SDR_type_12h_t SDR0 = {
    .hdr.recID_LSB = 0x00, /* record number, LSB - filled by sdr_init() */
    .hdr.recID_MSB = 0x00, /* record number, MSB - filled by sdr_init() */
    .hdr.SDRversion = 0x51, /* IPMI protocol version */
    .hdr.rectype = TYPE_12, /* record type: device locator record */
    .hdr.reclength = sizeof(SDR_type_12h_t) - sizeof(SDR_entry_hdr_t), /* record length - filled by sdr_init() */

/* record key bytes */
    .slaveaddr = 0x00,
    .chnum = 0x00,
    .power_notification_global_init = 0x04,
    .device_cap = 0x3b,
    .reserved[0] = 0x00,
    .reserved[1] = 0x00,
    .reserved[2] = 0x00,
    .entityID = 0xC1,
    .entityinstance = 0x00,
    .OEM = 0x00,
    .IDtypelen = 0xc0 | STR_SIZE(STR(TARGET_BOARD_NAME)), /* 8 bit ASCII, number of bytes */
    .IDstring = STR(TARGET_BOARD_NAME)
};

/* AMC Hot-Swap sensor */
const SDR_type_02h_t SDR_HOT_SWAP = {
    .hdr.recID_LSB = HOT_SWAP_SENSOR,
    .hdr.recID_MSB = 0x00,
    .hdr.SDRversion = 0x51,
    .hdr.rectype = TYPE_02,
    .hdr.reclength = sizeof(SDR_type_02h_t) - sizeof(SDR_entry_hdr_t),

    .ownerID = 0x00, /* i2c address, -> SDR_Init */
    .ownerLUN = 0x00, /* sensor owner LUN */
    .sensornum = HOT_SWAP_SENSOR, /* sensor number */

/* record body bytes */
    .entityID = 0xC1, /* entity id: AMC Module */
    .entityinstance = 0x00, /* entity instance -> SDR_Init */
    .sensorinit = 0x03, /* init: event generation + scanning enabled */
    .sensorcap = 0xc1, /* capabilities: auto re-arm,*/
    .sensortype = SENSOR_TYPE_HOT_SWAP, /* sensor type: HOT SWAP*/
    .event_reading_type = 0x6f, /* sensor reading*/
    .assertion_event_mask = { 0x00, /* LSB assert event mask: 3 bit value */
                              0x00 }, /* MSB assert event mask */
    .deassertion_event_mask = { 0x00, /* LSB deassert event mask: 3 bit value */
                                0x00 }, /* MSB deassert event mask */
    .readable_threshold_mask = 0x00, /* LSB: readable Threshold mask: no thresholds are readable:  */
    .settable_threshold_mask = 0x00, /* MSB: setable Threshold mask: no thresholds are setable: */
    .sensor_units_1 = 0xc0, /* sensor units 1 : Does not return analog reading*/
    .sensor_units_2 = 0x00, /* sensor units 2 :*/
    .sensor_units_3 = 0x00, /* sensor units 3 :*/
    .record_sharing[0] = 0x00,
    .record_sharing[1] = 0x00,
    .pos_thr_hysteresis = 0x00, /* positive going Threshold hysteresis value */
    .neg_thr_hysteresis = 0x00, /* negative going Threshold hysteresis value */
    .reserved1 = 0x00, /* reserved */
    .reserved2 = 0x00, /* reserved */
    .reserved3 = 0x00, /* reserved */
    .OEM = 0x00, /* OEM reserved */
    .IDtypelen = 0xc0 | STR_SIZE("HOTSWAP HANDLE"), /* 8 bit ASCII, number of bytes */
    .IDstring = "HOTSWAP HANDLE" /* sensor string */
};

/* FMC1 12V */
const SDR_type_01h_t SDR_FMC1_12V = {

    .hdr.recID_LSB = NUM_SDR_FMC1_12V,
    .hdr.recID_MSB = 0x00,
    .hdr.SDRversion = 0x51,
    .hdr.rectype = TYPE_01,
    .hdr.reclength = sizeof(SDR_type_01h_t) - sizeof(SDR_entry_hdr_t),

    .ownerID = 0x00, /* i2c address, -> SDR_Init */
    .ownerLUN = 0x00, /* sensor owner LUN */
    .sensornum = NUM_SDR_FMC1_12V, /* sensor number */

    /* record body bytes */
    .entityID = 0xC1, /* entity id: AMC Module */
    .entityinstance = 0x00, /* entity instance -> SDR_Init */
    .sensorinit = 0x7f, /* init: event generation + scanning enabled */
    .sensorcap = 0x68, /* capabilities: auto re-arm,*/
    .sensortype = SENSOR_TYPE_VOLTAGE, /* sensor type: Voltage*/
    .event_reading_type = 0x01, /* sensor reading*/
    .assertion_event_mask = { 0xFF, /* LSB assert event mask: 3 bit value */
                              0x0F }, /* MSB assert event mask */
    .deassertion_event_mask = { 0xFF, /* LSB deassert event mask: 3 bit value */
                                0x0F }, /* MSB deassert event mask */
    .readable_threshold_mask = 0x3F, /* LSB: readabled Threshold mask: all thresholds are readabled:  */
    .settable_threshold_mask = 0x3F, /* MSB: setabled Threshold mask: all thresholds are setabled: */
    .sensor_units_1 = 0x00, /* sensor units 1 :*/
    .sensor_units_2 = 0x04, /* sensor units 2 :*/
    .sensor_units_3 = 0x00, /* sensor units 3 :*/
    .linearization = 0x00, /* Linearization */
    .M = 64, /* M */
    .M_tol = 0x00, /* M - Tolerance */
    .B = 0x00, /* B */
    .B_accuracy = 0x00, /* B - Accuracy */
    .acc_exp_sensor_dir = 0x02, /* Sensor direction */
    .Rexp_Bexp = 0xD0, /* R-Exp = -3 , B-Exp = 0 */
    .analog_flags = 0x03, /* Analogue characteristics flags */
    .nominal_reading = 190, /* Nominal reading = 12.285V */
    .normal_max = 200, /* Normal maximum */
    .normal_min = 0, /* Normal minimum */
    .sensor_max_reading = 0xFF, /* Sensor Maximum reading */
    .sensor_min_reading = 0x00, /* Sensor Minimum reading */
    .upper_nonrecover_thr = 205, /* Upper non-recoverable Threshold */
    .upper_critical_thr = 200, /* Upper critical Threshold */
    .upper_noncritical_thr = 195, /* Upper non critical Threshold */
    .lower_nonrecover_thr = 175, /* Lower non-recoverable Threshold */
    .lower_critical_thr = 180, /* Lower critical Threshold */
    .lower_noncritical_thr = 185, /* Lower non-critical Threshold */
    .pos_thr_hysteresis = 2, /* positive going Threshold hysteresis value */
    .neg_thr_hysteresis = 2, /* negative going Threshold hysteresis value */
    .reserved1 = 0x00, /* reserved */
    .reserved2 = 0x00, /* reserved */
    .OEM = 0x00, /* OEM reserved */
    .IDtypelen = 0xc0 | STR_SIZE("FMC1 +12V") , /* 8 bit ASCII, number of bytes */
    .IDstring = "FMC1 +12V" /* sensor string */
};

/* FMC1 PVADJ */
const SDR_type_01h_t SDR_FMC1_VADJ = {

    .hdr.recID_LSB = NUM_SDR_FMC1_VADJ,
    .hdr.recID_MSB = 0x00,
    .hdr.SDRversion = 0x51,
    .hdr.rectype = TYPE_01,
    .hdr.reclength = sizeof(SDR_type_01h_t) - sizeof(SDR_entry_hdr_t),

    .ownerID = 0x00, /* i2c address, -> SDR_Init */
    .ownerLUN = 0x00, /* sensor owner LUN */
    .sensornum = NUM_SDR_FMC1_VADJ, /* sensor number */

    /* record body bytes */
    .entityID = 0xC1, /* entity id: AMC Module */
    .entityinstance = 0x00, /* entity instance -> SDR_Init */
    .sensorinit = 0x7f, /* init: event generation + scanning enabled */
    .sensorcap = 0x68, /* capabilities: auto re-arm,*/
    .sensortype = SENSOR_TYPE_VOLTAGE, /* sensor type: voltage*/
    .event_reading_type = 0x01, /* sensor reading*/
    .assertion_event_mask = { 0xFF, /* LSB assert event mask: 3 bit value */
                              0x0F }, /* MSB assert event mask */
    .deassertion_event_mask = { 0xFF, /* LSB deassert event mask: 3 bit value */
                                0x0F }, /* MSB deassert event mask */
    .readable_threshold_mask = 0x3F, /* LSB: readabled Threshold mask: all thresholds are readabled:  */
    .settable_threshold_mask = 0x3F, /* MSB: setabled Threshold mask: all thresholds are setabled: */
    .sensor_units_1 = 0x00, /* sensor units 1 :*/
    .sensor_units_2 = 0x04, /* sensor units 2 :*/
    .sensor_units_3 = 0x00, /* sensor units 3 :*/
    .linearization = 0x00, /* Linearization */
    .M = 64, /* M */
    .M_tol = 0x00, /* M - Tolerance */
    .B = 0x00, /* B */
    .B_accuracy = 0x00, /* B - Accuracy */
    .acc_exp_sensor_dir = 0x00, /* Sensor direction */
    .Rexp_Bexp = 0xD0, /* R-Exp , B-Exp */
    .analog_flags = 0x00, /* Analogue characteristics flags */
    .nominal_reading = 39, /* Nominal reading */
    .normal_max = 47, /* Normal maximum */
    .normal_min = 0, /* Normal minimum */
    .sensor_max_reading = 0xFF, /* Sensor Maximum reading */
    .sensor_min_reading = 0x00, /* Sensor Minimum reading */
    .upper_nonrecover_thr = 51, /* Upper non-recoverable Threshold */
    .upper_critical_thr = 46, /* Upper critical Threshold */
    .upper_noncritical_thr = 43, /* Upper non critical Threshold */
    .lower_nonrecover_thr = 28, /* Lower non-recoverable Threshold */
    .lower_critical_thr = 32, /* Lower critical Threshold */
    .lower_noncritical_thr = 36, /* Lower non-critical Threshold */
    .pos_thr_hysteresis = 2, /* positive going Threshold hysteresis value */
    .neg_thr_hysteresis = 2, /* negative going Threshold hysteresis value */
    .reserved1 = 0x00, /* reserved */
    .reserved2 = 0x00, /* reserved */
    .OEM = 0x00, /* OEM reserved */
    .IDtypelen = 0xc0 | STR_SIZE("FMC1 VADJ"), /* 8 bit ASCII, number of bytes */
    .IDstring = "FMC1 VADJ" /* sensor string */
};

/* FMC1 P3V3 */
const SDR_type_01h_t SDR_FMC1_P3V3 = {

    .hdr.recID_LSB = NUM_SDR_FMC1_3V3,
    .hdr.recID_MSB = 0x00,
    .hdr.SDRversion = 0x51,
    .hdr.rectype = TYPE_01,
    .hdr.reclength = sizeof(SDR_type_01h_t) - sizeof(SDR_entry_hdr_t),

    .ownerID = 0x00, /* i2c address, -> SDR_Init */
    .ownerLUN = 0x00, /* sensor owner LUN */
    .sensornum = NUM_SDR_FMC1_3V3, /* sensor number */

    /* record body bytes */
    .entityID = 0xC1, /* entity id: AMC Module */
    .entityinstance = 0x00, /* entity instance -> SDR_Init */
    .sensorinit = 0x7f, /* init: event generation + scanning enabled */
    .sensorcap = 0x68, /* capabilities: auto re-arm,*/
    .sensortype = SENSOR_TYPE_VOLTAGE, /* sensor type: VOLTAGE*/
    .event_reading_type = 0x01, /* sensor reading*/
    .assertion_event_mask = { 0xFF, /* LSB assert event mask: 3 bit value */
                              0x0F }, /* MSB assert event mask */
    .deassertion_event_mask = { 0xFF, /* LSB deassert event mask: 3 bit value */
                                0x0F }, /* MSB deassert event mask */
    .readable_threshold_mask = 0x3F, /* LSB: readabled Threshold mask: all thresholds are readabled:  */
    .settable_threshold_mask = 0x3F, /* MSB: setabled Threshold mask: all thresholds are setabled: */
    .sensor_units_1 = 0x00, /* sensor units 1 :*/
    .sensor_units_2 = 0x04, /* sensor units 2 :*/
    .sensor_units_3 = 0x00, /* sensor units 3 :*/
    .M = 64, /* M */
    .M_tol = 0x00, /* M - Tolerance */
    .B = 0x00, /* B */
    .B_accuracy = 0x00, /* B - Accuracy */
    .acc_exp_sensor_dir = 0x00, /* Sensor direction */
    .Rexp_Bexp = 0xD0, /* R-Exp , B-Exp */
    .analog_flags = 0x00, /* Analogue characteristics flags */
    .nominal_reading = 52, /* Nominal reading */
    .normal_max = 59, /* Normal maximum */
    .normal_min = 45, /* Normal minimum */
    .sensor_max_reading = 0xFF, /* Sensor Maximum reading */
    .sensor_min_reading = 0x00, /* Sensor Minimum reading */
    .upper_nonrecover_thr = 62, /* Upper non-recoverable Threshold */
    .upper_critical_thr = 59, /* Upper critical Threshold */
    .upper_noncritical_thr = 55, /* Upper non critical Threshold */
    .lower_nonrecover_thr = 42, /* Lower non-recoverable Threshold */
    .lower_critical_thr = 45, /* Lower critical Threshold */
    .lower_noncritical_thr = 48, /* Lower non-critical Threshold */
    .pos_thr_hysteresis = 2, /* positive going Threshold hysteresis value */
    .neg_thr_hysteresis = 2, /* negative going Threshold hysteresis value */
    .reserved1 = 0x00, /* reserved */
    .reserved2 = 0x00, /* reserved */
    .OEM = 0x00, /* OEM reserved */
    .IDtypelen = 0xc0 | STR_SIZE("FMC1 +3V3"), /* 8 bit ASCII, number of bytes */
    .IDstring = "FMC1 +3V3" /* sensor string */
};

/* FMC1 12V Current */
const SDR_type_01h_t SDR_FMC1_12V_CURR = {

    .hdr.recID_LSB = NUM_SDR_FMC1_12V_CURR,
    .hdr.recID_MSB = 0x00,
    .hdr.SDRversion = 0x51,
    .hdr.rectype = TYPE_01,
    .hdr.reclength = sizeof(SDR_type_01h_t) - sizeof(SDR_entry_hdr_t),

    .ownerID = 0x00, /* i2c address, -> SDR_Init */
    .ownerLUN = 0x00, /* sensor owner LUN */
    .sensornum = NUM_SDR_FMC1_12V_CURR, /* sensor number */

    /* record body bytes */
    .entityID = 0xC1, /* entity id: AMC Module */
    .entityinstance = 0x00, /* entity instance -> SDR_Init */
    .sensorinit = 0x7f, /* init: event generation + scanning enabled */
    .sensorcap = 0x68, /* capabilities: auto re-arm,*/
    .sensortype = SENSOR_TYPE_CURRENT, /* sensor type: Voltage*/
    .event_reading_type = 0x01, /* sensor reading*/
    .assertion_event_mask = { 0xFF, /* LSB assert event mask: 3 bit value */
                              0x0F }, /* MSB assert event mask */
    .deassertion_event_mask = { 0xFF, /* LSB deassert event mask: 3 bit value */
                                0x0F }, /* MSB deassert event mask */
    .readable_threshold_mask = 0x3F, /* LSB: readabled Threshold mask: all thresholds are readabled:  */
    .settable_threshold_mask = 0x3F, /* MSB: setabled Threshold mask: all thresholds are setabled: */
    .sensor_units_1 = 0x80, /* sensor units 1 :*/
    .sensor_units_2 = 0x05, /* sensor units 2 :*/
    .sensor_units_3 = 0x00, /* sensor units 3 :*/
    .linearization = 0x00, /* Linearization */
    .M = 32, /* M */
    .M_tol = 0x00, /* M - Tolerance */
    .B = 0x00, /* B */
    .B_accuracy = 0x00, /* B - Accuracy */
    .acc_exp_sensor_dir = 0x02, /* Sensor direction */
    .Rexp_Bexp = 0xD0, /* R-Exp = -3 , B-Exp = 0 */
    .analog_flags = 0x03, /* Analogue characteristics flags */
    .nominal_reading = 190, /* Nominal reading = 12.285V */
    .normal_max = 156, /* Normal maximum - 5A per sensor */
    .normal_min = 0, /* Normal minimum */
    .sensor_max_reading = 0xFF, /* Sensor Maximum reading */
    .sensor_min_reading = 0x00, /* Sensor Minimum reading */
    .upper_nonrecover_thr = 100, /* Upper non-recoverable Threshold */
    .upper_critical_thr = 90, /* Upper critical Threshold */
    .upper_noncritical_thr = 80, /* Upper non critical Threshold */
    .lower_nonrecover_thr = -60, /* Lower non-recoverable Threshold */
    .lower_critical_thr = -50, /* Lower critical Threshold */
    .lower_noncritical_thr = 10, /* Lower non-critical Threshold */
    .pos_thr_hysteresis = 2, /* positive going Threshold hysteresis value */
    .neg_thr_hysteresis = 2, /* negative going Threshold hysteresis value */
    .reserved1 = 0x00, /* reserved */
    .reserved2 = 0x00, /* reserved */
    .OEM = 0x00, /* OEM reserved */
    .IDtypelen = 0xc0 | STR_SIZE("FMC1 +12V CURR") , /* 8 bit ASCII, number of bytes */
    .IDstring = "FMC1 +12V CURR" /* sensor string */
};

/* FMC1 PVADJ Current */
const SDR_type_01h_t SDR_FMC1_VADJ_CURR = {

    .hdr.recID_LSB = NUM_SDR_FMC1_VADJ_CURR,
    .hdr.recID_MSB = 0x00,
    .hdr.SDRversion = 0x51,
    .hdr.rectype = TYPE_01,
    .hdr.reclength = sizeof(SDR_type_01h_t) - sizeof(SDR_entry_hdr_t),

    .ownerID = 0x00, /* i2c address, -> SDR_Init */
    .ownerLUN = 0x00, /* sensor owner LUN */
    .sensornum = NUM_SDR_FMC1_VADJ_CURR, /* sensor number */

    /* record body bytes */
    .entityID = 0xC1, /* entity id: AMC Module */
    .entityinstance = 0x00, /* entity instance -> SDR_Init */
    .sensorinit = 0x7f, /* init: event generation + scanning enabled */
    .sensorcap = 0x68, /* capabilities: auto re-arm,*/
    .sensortype = SENSOR_TYPE_CURRENT, /* sensor type: voltage*/
    .event_reading_type = 0x01, /* sensor reading*/
    .assertion_event_mask = { 0xFF, /* LSB assert event mask: 3 bit value */
                              0x0F }, /* MSB assert event mask */
    .deassertion_event_mask = { 0xFF, /* LSB deassert event mask: 3 bit value */
                                0x0F }, /* MSB deassert event mask */
    .readable_threshold_mask = 0x3F, /* LSB: readabled Threshold mask: all thresholds are readabled:  */
    .settable_threshold_mask = 0x3F, /* MSB: setabled Threshold mask: all thresholds are setabled: */
    .sensor_units_1 = 0x80, /* sensor units 1 :*/
    .sensor_units_2 = 0x05, /* sensor units 2 :*/
    .sensor_units_3 = 0x00, /* sensor units 3 :*/
    .linearization = 0x00, /* Linearization */
    .M = 32, /* M -> Current LSB*20 */
    .M_tol = 0x00, /* M - Tolerance */
    .B = 0x00, /* B */
    .B_accuracy = 0x00, /* B - Accuracy */
    .acc_exp_sensor_dir = 0x00, /* Sensor direction */
    .Rexp_Bexp = 0xD0, /* R-Exp , B-Exp */
    .analog_flags = 0x00, /* Analogue characteristics flags */
    .nominal_reading = 39, /* Nominal reading */
    .normal_max = 47, /* Normal maximum */
    .normal_min = 0, /* Normal minimum */
    .sensor_max_reading = 0x7F, /* Sensor Maximum reading */
    .sensor_min_reading = 0x80, /* Sensor Minimum reading */
    .upper_nonrecover_thr = 100, /* Upper non-recoverable Threshold */
    .upper_critical_thr = 90, /* Upper critical Threshold */
    .upper_noncritical_thr = 80, /* Upper non critical Threshold */
    .lower_nonrecover_thr = -60, /* Lower non-recoverable Threshold */
    .lower_critical_thr = -50, /* Lower critical Threshold */
    .lower_noncritical_thr = 10, /* Lower non-critical Threshold */
    .pos_thr_hysteresis = 2, /* positive going Threshold hysteresis value */
    .neg_thr_hysteresis = 2, /* negative going Threshold hysteresis value */
    .reserved1 = 0x00, /* reserved */
    .reserved2 = 0x00, /* reserved */
    .OEM = 0x00, /* OEM reserved */
    .IDtypelen = 0xc0 | STR_SIZE("FMC1 VADJ CURR"), /* 8 bit ASCII, number of bytes */
    .IDstring = "FMC1 VADJ CURR" /* sensor string */
};

/* FMC1 P3V3 Current */
const SDR_type_01h_t SDR_FMC1_P3V3_CURR = {

    .hdr.recID_LSB = NUM_SDR_FMC1_3V3_CURR,
    .hdr.recID_MSB = 0x00,
    .hdr.SDRversion = 0x51,
    .hdr.rectype = TYPE_01,
    .hdr.reclength = sizeof(SDR_type_01h_t) - sizeof(SDR_entry_hdr_t),

    .ownerID = 0x00, /* i2c address, -> SDR_Init */
    .ownerLUN = 0x00, /* sensor owner LUN */
    .sensornum = NUM_SDR_FMC1_3V3_CURR, /* sensor number */

    /* record body bytes */
    .entityID = 0xC1, /* entity id: AMC Module */
    .entityinstance = 0x00, /* entity instance -> SDR_Init */
    .sensorinit = 0x7f, /* init: event generation + scanning enabled */
    .sensorcap = 0x68, /* capabilities: auto re-arm,*/
    .sensortype = SENSOR_TYPE_CURRENT, /* sensor type: VOLTAGE*/
    .event_reading_type = 0x01, /* sensor reading*/
    .assertion_event_mask = { 0xFF, /* LSB assert event mask: 3 bit value */
                              0x0F }, /* MSB assert event mask */
    .deassertion_event_mask = { 0xFF, /* LSB deassert event mask: 3 bit value */
                                0x0F }, /* MSB deassert event mask */
    .readable_threshold_mask = 0x3F, /* LSB: readabled Threshold mask: all thresholds are readabled:  */
    .settable_threshold_mask = 0x3F, /* MSB: setabled Threshold mask: all thresholds are setabled: */
    .sensor_units_1 = 0x80, /* sensor units 1 :*/
    .sensor_units_2 = 0x05, /* sensor units 2 :*/
    .sensor_units_3 = 0x00, /* sensor units 3 :*/
    .M = 32, /* M */
    .M_tol = 0x00, /* M - Tolerance */
    .B = 0x00, /* B */
    .B_accuracy = 0x00, /* B - Accuracy */
    .acc_exp_sensor_dir = 0x00, /* Sensor direction */
    .Rexp_Bexp = 0xD0, /* R-Exp , B-Exp */
    .analog_flags = 0x00, /* Analogue characteristics flags */
    .nominal_reading = 52, /* Nominal reading */
    .normal_max = 59, /* Normal maximum */
    .normal_min = 45, /* Normal minimum */
    .sensor_max_reading = 0xFF, /* Sensor Maximum reading */
    .sensor_min_reading = 0x00, /* Sensor Minimum reading */
    .upper_nonrecover_thr = 100, /* Upper non-recoverable Threshold */
    .upper_critical_thr = 90, /* Upper critical Threshold */
    .upper_noncritical_thr = 80, /* Upper non critical Threshold */
    .lower_nonrecover_thr = -60, /* Lower non-recoverable Threshold */
    .lower_critical_thr = -50, /* Lower critical Threshold */
    .lower_noncritical_thr = 10, /* Lower non-critical Threshold */
    .pos_thr_hysteresis = 2, /* positive going Threshold hysteresis value */
    .neg_thr_hysteresis = 2, /* negative going Threshold hysteresis value */
    .reserved1 = 0x00, /* reserved */
    .reserved2 = 0x00, /* reserved */
    .OEM = 0x00, /* OEM reserved */
    .IDtypelen = 0xc0 | STR_SIZE("FMC1 +3V3 CURR"), /* 8 bit ASCII, number of bytes */
    .IDstring = "FMC1 +3V3 CURR" /* sensor string */
};

/* FMC2 12V */
const SDR_type_01h_t SDR_FMC2_12V = {

    .hdr.recID_LSB = NUM_SDR_FMC2_12V,
    .hdr.recID_MSB = 0x00,
    .hdr.SDRversion = 0x51,
    .hdr.rectype = TYPE_01,
    .hdr.reclength = sizeof(SDR_type_01h_t) - sizeof(SDR_entry_hdr_t),

    .ownerID = 0x00, /* i2c address, -> SDR_Init */
    .ownerLUN = 0x00, /* sensor owner LUN */
    .sensornum = NUM_SDR_FMC2_12V, /* sensor number */

    /* record body bytes */
    .entityID = 0xC1, /* entity id: AMC Module */
    .entityinstance = 0x00, /* entity instance -> SDR_Init */
    .sensorinit = 0x7f, /* init: event generation + scanning enabled */
    .sensorcap = 0x68, /* capabilities: auto re-arm,*/
    .sensortype = SENSOR_TYPE_VOLTAGE, /* sensor type: Voltage*/
    .event_reading_type = 0x01, /* sensor reading*/
    .assertion_event_mask = { 0xFF, /* LSB assert event mask: 3 bit value */
                              0x0F }, /* MSB assert event mask */
    .deassertion_event_mask = { 0xFF, /* LSB deassert event mask: 3 bit value */
                                0x0F }, /* MSB deassert event mask */
    .readable_threshold_mask = 0x3F, /* LSB: readabled Threshold mask: all thresholds are readabled:  */
    .settable_threshold_mask = 0x3F, /* MSB: setabled Threshold mask: all thresholds are setabled: */
    .sensor_units_1 = 0x00, /* sensor units 1 :*/
    .sensor_units_2 = 0x04, /* sensor units 2 :*/
    .sensor_units_3 = 0x00, /* sensor units 3 :*/
    .linearization = 0x00, /* Linearization */
    .M = 64, /* M */
    .M_tol = 0x00, /* M - Tolerance */
    .B = 0x00, /* B */
    .B_accuracy = 0x00, /* B - Accuracy */
    .acc_exp_sensor_dir = 0x02, /* Sensor direction */
    .Rexp_Bexp = 0xD0, /* R-Exp = -3 , B-Exp = 0 */
    .analog_flags = 0x03, /* Analogue characteristics flags */
    .nominal_reading = 190, /* Nominal reading = 12.285V */
    .normal_max = 200, /* Normal maximum */
    .normal_min = 0, /* Normal minimum */
    .sensor_max_reading = 0xFF, /* Sensor Maximum reading */
    .sensor_min_reading = 0x00, /* Sensor Minimum reading */
    .upper_nonrecover_thr = 205, /* Upper non-recoverable Threshold */
    .upper_critical_thr = 200, /* Upper critical Threshold */
    .upper_noncritical_thr = 195, /* Upper non critical Threshold */
    .lower_nonrecover_thr = 175, /* Lower non-recoverable Threshold */
    .lower_critical_thr = 180, /* Lower critical Threshold */
    .lower_noncritical_thr = 185, /* Lower non-critical Threshold */
    .pos_thr_hysteresis = 2, /* positive going Threshold hysteresis value */
    .neg_thr_hysteresis = 2, /* negative going Threshold hysteresis value */    .reserved1 = 0x00, /* reserved */
    .reserved2 = 0x00, /* reserved */
    .OEM = 0x00, /* OEM reserved */
    .IDtypelen = 0xc0 | STR_SIZE("FMC2 +12V") , /* 8 bit ASCII, number of bytes */
    .IDstring = "FMC2 +12V" /* sensor string */
};

/* FMC2 PVADJ */
const SDR_type_01h_t SDR_FMC2_VADJ = {

    .hdr.recID_LSB = NUM_SDR_FMC2_VADJ,
    .hdr.recID_MSB = 0x00,
    .hdr.SDRversion = 0x51,
    .hdr.rectype = TYPE_01,
    .hdr.reclength = sizeof(SDR_type_01h_t) - sizeof(SDR_entry_hdr_t),

    .ownerID = 0x00, /* i2c address, -> SDR_Init */
    .ownerLUN = 0x00, /* sensor owner LUN */
    .sensornum = NUM_SDR_FMC2_VADJ, /* sensor number */

    /* record body bytes */
    .entityID = 0xC1, /* entity id: AMC Module */
    .entityinstance = 0x00, /* entity instance -> SDR_Init */
    .sensorinit = 0x7f, /* init: event generation + scanning enabled */
    .sensorcap = 0x68, /* capabilities: auto re-arm,*/
    .sensortype = SENSOR_TYPE_VOLTAGE, /* sensor type: voltage*/
    .event_reading_type = 0x01, /* sensor reading*/
    .assertion_event_mask = { 0xFF, /* LSB assert event mask: 3 bit value */
                              0x0F }, /* MSB assert event mask */
    .deassertion_event_mask = { 0xFF, /* LSB deassert event mask: 3 bit value */
                                0x0F }, /* MSB deassert event mask */
    .readable_threshold_mask = 0x3F, /* LSB: readabled Threshold mask: all thresholds are readabled:  */
    .settable_threshold_mask = 0x3F, /* MSB: setabled Threshold mask: all thresholds are setabled: */
    .sensor_units_1 = 0x00, /* sensor units 1 :*/
    .sensor_units_2 = 0x04, /* sensor units 2 :*/
    .sensor_units_3 = 0x00, /* sensor units 3 :*/
    .linearization = 0x00, /* Linearization */
    .M = 64, /* M */
    .M_tol = 0x00, /* M - Tolerance */
    .B = 0x00, /* B */
    .B_accuracy = 0x00, /* B - Accuracy */
    .acc_exp_sensor_dir = 0x00, /* Sensor direction */
    .Rexp_Bexp = 0xD0, /* R-Exp , B-Exp */
    .analog_flags = 0x00, /* Analogue characteristics flags */
    .nominal_reading = 39, /* Nominal reading */
    .normal_max = 47, /* Normal maximum */
    .normal_min = 0, /* Normal minimum */
    .sensor_max_reading = 0xFF, /* Sensor Maximum reading */
    .sensor_min_reading = 0x00, /* Sensor Minimum reading */
    .upper_nonrecover_thr = 51, /* Upper non-recoverable Threshold */
    .upper_critical_thr = 46, /* Upper critical Threshold */
    .upper_noncritical_thr = 43, /* Upper non critical Threshold */
    .lower_nonrecover_thr = 28, /* Lower non-recoverable Threshold */
    .lower_critical_thr = 32, /* Lower critical Threshold */
    .lower_noncritical_thr = 36, /* Lower non-critical Threshold */
    .pos_thr_hysteresis = 2, /* positive going Threshold hysteresis value */
    .neg_thr_hysteresis = 2, /* negative going Threshold hysteresis value */
    .reserved1 = 0x00, /* reserved */
    .reserved2 = 0x00, /* reserved */
    .OEM = 0x00, /* OEM reserved */
    .IDtypelen = 0xc0 | STR_SIZE("FMC2 VADJ"), /* 8 bit ASCII, number of bytes */
    .IDstring = "FMC2 VADJ" /* sensor string */
};

/* FMC2 P3V3 */
const SDR_type_01h_t SDR_FMC2_P3V3 = {

    .hdr.recID_LSB = NUM_SDR_FMC2_3V3,
    .hdr.recID_MSB = 0x00,
    .hdr.SDRversion = 0x51,
    .hdr.rectype = TYPE_01,
    .hdr.reclength = sizeof(SDR_type_01h_t) - sizeof(SDR_entry_hdr_t),

    .ownerID = 0x00, /* i2c address, -> SDR_Init */
    .ownerLUN = 0x00, /* sensor owner LUN */
    .sensornum = NUM_SDR_FMC2_3V3, /* sensor number */

    /* record body bytes */
    .entityID = 0xC1, /* entity id: AMC Module */
    .entityinstance = 0x00, /* entity instance -> SDR_Init */
    .sensorinit = 0x7f, /* init: event generation + scanning enabled */
    .sensorcap = 0x68, /* capabilities: auto re-arm,*/
    .sensortype = SENSOR_TYPE_VOLTAGE, /* sensor type: VOLTAGE*/
    .event_reading_type = 0x01, /* sensor reading*/
    .assertion_event_mask = { 0xFF, /* LSB assert event mask: 3 bit value */
                              0x0F }, /* MSB assert event mask */
    .deassertion_event_mask = { 0xFF, /* LSB deassert event mask: 3 bit value */
                                0x0F }, /* MSB deassert event mask */
    .readable_threshold_mask = 0x3F, /* LSB: readabled Threshold mask: all thresholds are readabled:  */
    .settable_threshold_mask = 0x3F, /* MSB: setabled Threshold mask: all thresholds are setabled: */
    .sensor_units_1 = 0x00, /* sensor units 1 :*/
    .sensor_units_2 = 0x04, /* sensor units 2 :*/
    .sensor_units_3 = 0x00, /* sensor units 3 :*/
    .linearization = 0x00, /* Linearization */
    .M = 64, /* M */
    .M_tol = 0x00, /* M - Tolerance */
    .B = 0x00, /* B */
    .B_accuracy = 0x00, /* B - Accuracy */
    .acc_exp_sensor_dir = 0x00, /* Sensor direction */
    .Rexp_Bexp = 0xD0, /* R-Exp , B-Exp */
    .analog_flags = 0x00, /* Analogue characteristics flags */
    .nominal_reading = 52, /* Nominal reading */
    .normal_max = 59, /* Normal maximum */
    .normal_min = 45, /* Normal minimum */
    .sensor_max_reading = 0xFF, /* Sensor Maximum reading */
    .sensor_min_reading = 0x00, /* Sensor Minimum reading */
    .upper_nonrecover_thr = 62, /* Upper non-recoverable Threshold */
    .upper_critical_thr = 59, /* Upper critical Threshold */
    .upper_noncritical_thr = 55, /* Upper non critical Threshold */
    .lower_nonrecover_thr = 42, /* Lower non-recoverable Threshold */
    .lower_critical_thr = 45, /* Lower critical Threshold */
    .lower_noncritical_thr = 48, /* Lower non-critical Threshold */
    .pos_thr_hysteresis = 2, /* positive going Threshold hysteresis value */
    .neg_thr_hysteresis = 2, /* negative going Threshold hysteresis value */
    .reserved1 = 0x00, /* reserved */
    .reserved2 = 0x00, /* reserved */
    .OEM = 0x00, /* OEM reserved */
    .IDtypelen = 0xc0 | STR_SIZE("FMC2 +3V3"), /* 8 bit ASCII, number of bytes */
    .IDstring = "FMC2 +3V3" /* sensor string */
};

/* FMC2 12V Current */
const SDR_type_01h_t SDR_FMC2_12V_CURR = {

    .hdr.recID_LSB = NUM_SDR_FMC2_12V_CURR,
    .hdr.recID_MSB = 0x00,
    .hdr.SDRversion = 0x51,
    .hdr.rectype = TYPE_01,
    .hdr.reclength = sizeof(SDR_type_01h_t) - sizeof(SDR_entry_hdr_t),

    .ownerID = 0x00, /* i2c address, -> SDR_Init */
    .ownerLUN = 0x00, /* sensor owner LUN */
    .sensornum = NUM_SDR_FMC2_12V_CURR, /* sensor number */

    /* record body bytes */
    .entityID = 0xC1, /* entity id: AMC Module */
    .entityinstance = 0x00, /* entity instance -> SDR_Init */
    .sensorinit = 0x7f, /* init: event generation + scanning enabled */
    .sensorcap = 0x68, /* capabilities: auto re-arm,*/
    .sensortype = SENSOR_TYPE_CURRENT, /* sensor type: Voltage*/
    .event_reading_type = 0x01, /* sensor reading*/
    .assertion_event_mask = { 0xFF, /* LSB assert event mask: 3 bit value */
                              0x0F }, /* MSB assert event mask */
    .deassertion_event_mask = { 0xFF, /* LSB deassert event mask: 3 bit value */
                                0x0F }, /* MSB deassert event mask */
    .readable_threshold_mask = 0x3F, /* LSB: readabled Threshold mask: all thresholds are readabled:  */
    .settable_threshold_mask = 0x3F, /* MSB: setabled Threshold mask: all thresholds are setabled: */
    .sensor_units_1 = 0x80, /* sensor units 1 :*/
    .sensor_units_2 = 0x05, /* sensor units 2 :*/
    .sensor_units_3 = 0x00, /* sensor units 3 :*/
    .linearization = 0x00, /* Linearization */
    .M = 32, /* M */
    .M_tol = 0x00, /* M - Tolerance */
    .B = 0x00, /* B */
    .B_accuracy = 0x00, /* B - Accuracy */
    .acc_exp_sensor_dir = 0x02, /* Sensor direction */
    .Rexp_Bexp = 0xD0, /* R-Exp = -3 , B-Exp = 0 */
    .analog_flags = 0x03, /* Analogue characteristics flags */
    .nominal_reading = 190, /* Nominal reading = 12.285V */
    .normal_max = 200, /* Normal maximum */
    .normal_min = 0, /* Normal minimum */
    .sensor_max_reading = 0xFF, /* Sensor Maximum reading */
    .sensor_min_reading = 0x00, /* Sensor Minimum reading */
    .upper_nonrecover_thr = 100, /* Upper non-recoverable Threshold */
    .upper_critical_thr = 90, /* Upper critical Threshold */
    .upper_noncritical_thr = 80, /* Upper non critical Threshold */
    .lower_nonrecover_thr = -60, /* Lower non-recoverable Threshold */
    .lower_critical_thr = -50, /* Lower critical Threshold */
    .lower_noncritical_thr = 10, /* Lower non-critical Threshold */
    .pos_thr_hysteresis = 2, /* positive going Threshold hysteresis value */
    .neg_thr_hysteresis = 2, /* negative going Threshold hysteresis value */
    .reserved1 = 0x00, /* reserved */
    .reserved2 = 0x00, /* reserved */
    .OEM = 0x00, /* OEM reserved */
    .IDtypelen = 0xc0 | STR_SIZE("FMC2 +12V CURR") , /* 8 bit ASCII, number of bytes */
    .IDstring = "FMC2 +12V CURR" /* sensor string */
};

/* FMC2 PVADJ Current */
const SDR_type_01h_t SDR_FMC2_VADJ_CURR = {

    .hdr.recID_LSB = NUM_SDR_FMC2_VADJ_CURR,
    .hdr.recID_MSB = 0x00,
    .hdr.SDRversion = 0x51,
    .hdr.rectype = TYPE_01,
    .hdr.reclength = sizeof(SDR_type_01h_t) - sizeof(SDR_entry_hdr_t),

    .ownerID = 0x00, /* i2c address, -> SDR_Init */
    .ownerLUN = 0x00, /* sensor owner LUN */
    .sensornum = NUM_SDR_FMC2_VADJ_CURR, /* sensor number */

    /* record body bytes */
    .entityID = 0xC1, /* entity id: AMC Module */
    .entityinstance = 0x00, /* entity instance -> SDR_Init */
    .sensorinit = 0x7f, /* init: event generation + scanning enabled */
    .sensorcap = 0x68, /* capabilities: auto re-arm,*/
    .sensortype = SENSOR_TYPE_CURRENT, /* sensor type: voltage*/
    .event_reading_type = 0x01, /* sensor reading*/
    .assertion_event_mask = { 0xFF, /* LSB assert event mask: 3 bit value */
                              0x0F }, /* MSB assert event mask */
    .deassertion_event_mask = { 0xFF, /* LSB deassert event mask: 3 bit value */
                                0x0F }, /* MSB deassert event mask */
    .readable_threshold_mask = 0x3F, /* LSB: readabled Threshold mask: all thresholds are readabled:  */
    .settable_threshold_mask = 0x3F, /* MSB: setabled Threshold mask: all thresholds are setabled: */
    .sensor_units_1 = 0x80, /* sensor units 1 :*/
    .sensor_units_2 = 0x05, /* sensor units 2 :*/
    .sensor_units_3 = 0x00, /* sensor units 3 :*/
    .linearization = 0x00, /* Linearization */
    .M = 32, /* M */
    .M_tol = 0x00, /* M - Tolerance */
    .B = 0x00, /* B */
    .B_accuracy = 0x00, /* B - Accuracy */
    .acc_exp_sensor_dir = 0x00, /* Sensor direction */
    .Rexp_Bexp = 0xD0, /* R-Exp , B-Exp */
    .analog_flags = 0x00, /* Analogue characteristics flags */
    .nominal_reading = 39, /* Nominal reading */
    .normal_max = 47, /* Normal maximum */
    .normal_min = 0, /* Normal minimum */
    .sensor_max_reading = 0xFF, /* Sensor Maximum reading */
    .sensor_min_reading = 0x00, /* Sensor Minimum reading */
    .upper_nonrecover_thr = 100, /* Upper non-recoverable Threshold */
    .upper_critical_thr = 90, /* Upper critical Threshold */
    .upper_noncritical_thr = 80, /* Upper non critical Threshold */
    .lower_nonrecover_thr = -60, /* Lower non-recoverable Threshold */
    .lower_critical_thr = -50, /* Lower critical Threshold */
    .lower_noncritical_thr = 10, /* Lower non-critical Threshold */
    .pos_thr_hysteresis = 2, /* positive going Threshold hysteresis value */
    .neg_thr_hysteresis = 2, /* negative going Threshold hysteresis value */
    .reserved1 = 0x00, /* reserved */
    .reserved2 = 0x00, /* reserved */
    .OEM = 0x00, /* OEM reserved */
    .IDtypelen = 0xc0 | STR_SIZE("FMC2 VADJ CURR"), /* 8 bit ASCII, number of bytes */
    .IDstring = "FMC2 VADJ CURR" /* sensor string */
};

/* FMC2 P3V3 Current */
const SDR_type_01h_t SDR_FMC2_P3V3_CURR = {

    .hdr.recID_LSB = NUM_SDR_FMC2_3V3_CURR,
    .hdr.recID_MSB = 0x00,
    .hdr.SDRversion = 0x51,
    .hdr.rectype = TYPE_01,
    .hdr.reclength = sizeof(SDR_type_01h_t) - sizeof(SDR_entry_hdr_t),

    .ownerID = 0x00, /* i2c address, -> SDR_Init */
    .ownerLUN = 0x00, /* sensor owner LUN */
    .sensornum = NUM_SDR_FMC2_3V3_CURR, /* sensor number */

    /* record body bytes */
    .entityID = 0xC1, /* entity id: AMC Module */
    .entityinstance = 0x00, /* entity instance -> SDR_Init */
    .sensorinit = 0x7f, /* init: event generation + scanning enabled */
    .sensorcap = 0x68, /* capabilities: auto re-arm,*/
    .sensortype = SENSOR_TYPE_CURRENT, /* sensor type: VOLTAGE*/
    .event_reading_type = 0x01, /* sensor reading*/
    .assertion_event_mask = { 0xFF, /* LSB assert event mask: 3 bit value */
                              0x0F }, /* MSB assert event mask */
    .deassertion_event_mask = { 0xFF, /* LSB deassert event mask: 3 bit value */
                                0x0F }, /* MSB deassert event mask */
    .readable_threshold_mask = 0x3F, /* LSB: readabled Threshold mask: all thresholds are readabled:  */
    .settable_threshold_mask = 0x3F, /* MSB: setabled Threshold mask: all thresholds are setabled: */
    .sensor_units_1 = 0x80, /* sensor units 1 :*/
    .sensor_units_2 = 0x05, /* sensor units 2 :*/
    .sensor_units_3 = 0x00, /* sensor units 3 :*/
    .M = 32, /* M */
    .M_tol = 0x00, /* M - Tolerance */
    .B = 0x00, /* B */
    .B_accuracy = 0x00, /* B - Accuracy */
    .acc_exp_sensor_dir = 0x00, /* Sensor direction */
    .Rexp_Bexp = 0xD0, /* R-Exp , B-Exp */
    .analog_flags = 0x00, /* Analogue characteristics flags */
    .nominal_reading = 52, /* Nominal reading */
    .normal_max = 59, /* Normal maximum */
    .normal_min = 45, /* Normal minimum */
    .sensor_max_reading = 0xFF, /* Sensor Maximum reading */
    .sensor_min_reading = 0x00, /* Sensor Minimum reading */
    .upper_nonrecover_thr = 100, /* Upper non-recoverable Threshold */
    .upper_critical_thr = 90, /* Upper critical Threshold */
    .upper_noncritical_thr = 80, /* Upper non critical Threshold */
    .lower_nonrecover_thr = -60, /* Lower non-recoverable Threshold */
    .lower_critical_thr = -50, /* Lower critical Threshold */
    .lower_noncritical_thr = 10, /* Lower non-critical Threshold */
    .pos_thr_hysteresis = 2, /* positive going Threshold hysteresis value */
    .neg_thr_hysteresis = 2, /* negative going Threshold hysteresis value */
    .reserved1 = 0x00, /* reserved */
    .reserved2 = 0x00, /* reserved */
    .OEM = 0x00, /* OEM reserved */
    .IDtypelen = 0xc0 | STR_SIZE("FMC2 +3V3 CURR"), /* 8 bit ASCII, number of bytes */
    .IDstring = "FMC2 +3V3 CURR" /* sensor string */
};

const SDR_type_01h_t SDR_LM75_uC = {

    .hdr.recID_LSB = NUM_SDR_LM75_uC,
    .hdr.recID_MSB = 0x00,
    .hdr.SDRversion = 0x51,
    .hdr.rectype = TYPE_01,
    .hdr.reclength = sizeof(SDR_type_01h_t) - sizeof(SDR_entry_hdr_t),

    .ownerID = 0x00, /* i2c address, -> SDR_Init */
    .ownerLUN = 0x00, /* sensor owner LUN */
    .sensornum = NUM_SDR_LM75_uC, /* sensor number */

    /* record body bytes */
    .entityID = 0xC1, /* entity id: AMC Module */
    .entityinstance = 0x00, /* entity instance -> SDR_Init */
    .sensorinit = 0x7f, /* init: event generation + scanning enabled */
    .sensorcap = 0x68, /* capabilities: auto re-arm,*/
    .sensortype = SENSOR_TYPE_TEMPERATURE, /* sensor type */
    .event_reading_type = 0x01, /* sensor reading*/
    .assertion_event_mask = { 0xFF, /* LSB assert event mask: 3 bit value */
                              0x0F }, /* MSB assert event mask */
    .deassertion_event_mask = { 0xFF, /* LSB deassert event mask: 3 bit value */
                                0x0F }, /* MSB deassert event mask */
    .readable_threshold_mask = 0x3F, /* LSB: readabled Threshold mask: all thresholds are readabled:  */
    .settable_threshold_mask = 0x3F, /* MSB: setabled Threshold mask: all thresholds are setabled: */
    .sensor_units_1 = 0x00, /* sensor units 1 :*/
    .sensor_units_2 = 0x01, /* sensor units 2 :*/
    .sensor_units_3 = 0x00, /* sensor units 3 :*/
    .linearization = 0x00, /* Linearization */
    .M = 5, /* M */
    .M_tol = 0x00, /* M - Tolerance */
    .B = 0x00, /* B */
    .B_accuracy = 0x00, /* B - Accuracy */
    .acc_exp_sensor_dir = 0x00, /* Sensor direction */
    .Rexp_Bexp = 0xF0, /* R-Exp , B-Exp */
    .analog_flags = 0x03, /* Analogue characteristics flags */
    .nominal_reading = (30 << 1), /* Nominal reading */
    .normal_max = (50 << 1), /* Normal maximum */
    .normal_min = (20 << 1), /* Normal minimum */
    .sensor_max_reading = 0xFF, /* Sensor Maximum reading */
    .sensor_min_reading = 0x00, /* Sensor Minimum reading */
    .upper_nonrecover_thr = (75 << 1), /* Upper non-recoverable Threshold */
    .upper_critical_thr = (65 << 1), /* Upper critical Threshold */
    .upper_noncritical_thr = (55 << 1), /* Upper non critical Threshold */
    .lower_nonrecover_thr = (5 << 1), /* Lower non-recoverable Threshold */
    .lower_critical_thr = (10 << 1), /* Lower critical Threshold */
    .lower_noncritical_thr = (20 << 1), /* Lower non-critical Threshold */
    .pos_thr_hysteresis = 2, /* positive going Threshold hysteresis value */
    .neg_thr_hysteresis = 2, /* negative going Threshold hysteresis value */
    .reserved1 = 0x00, /* reserved */
    .reserved2 = 0x00, /* reserved */
    .OEM = 0x00, /* OEM reserved */
    .IDtypelen = 0xc0 | STR_SIZE("TEMP UC"), /* 8 bit ASCII, number of bytes */
    .IDstring = "TEMP UC" /*  sensor string */
};

const SDR_type_01h_t SDR_LM75_CLOCK_SWITCH = {

    .hdr.recID_LSB = NUM_SDR_LM75_CLOCK_SWITCH,
    .hdr.recID_MSB = 0x00,
    .hdr.SDRversion = 0x51,
    .hdr.rectype = TYPE_01,
    .hdr.reclength = sizeof(SDR_type_01h_t) - sizeof(SDR_entry_hdr_t),

    .ownerID = 0x00, /* i2c address, -> SDR_Init */
    .ownerLUN = 0x00, /* sensor owner LUN */
    .sensornum = NUM_SDR_LM75_CLOCK_SWITCH, /* sensor number */

    /* record body bytes */
    .entityID = 0xC1, /* entity id: AMC Module */
    .entityinstance = 0x00, /* entity instance -> SDR_Init */
    .sensorinit = 0x7f, /* init: event generation + scanning enabled */
    .sensorcap = 0x68, /* capabilities: auto re-arm,*/
    .sensortype = SENSOR_TYPE_TEMPERATURE, /* sensor type */
    .event_reading_type = 0x01, /* sensor reading*/
    .assertion_event_mask = { 0xFF, /* LSB assert event mask: 3 bit value */
                              0x0F }, /* MSB assert event mask */
    .deassertion_event_mask = { 0xFF, /* LSB deassert event mask: 3 bit value */
                                0x0F }, /* MSB deassert event mask */
    .readable_threshold_mask = 0x3F, /* LSB: readabled Threshold mask: all thresholds are readabled:  */
    .settable_threshold_mask = 0x3F, /* MSB: setabled Threshold mask: all thresholds are setabled: */
    .sensor_units_1 = 0x00, /* sensor units 1 :*/
    .sensor_units_2 = 0x01, /* sensor units 2 :*/
    .sensor_units_3 = 0x00, /* sensor units 3 :*/
    .linearization = 0x00, /* Linearization */
    .M = 5, /* M */
    .M_tol = 0x00, /* M - Tolerance */
    .B = 0x00, /* B */
    .B_accuracy = 0x00, /* B - Accuracy */
    .acc_exp_sensor_dir = 0x00, /* Sensor direction */
    .Rexp_Bexp = 0xF0, /* R-Exp , B-Exp */
    .analog_flags = 0x03, /* Analogue characteristics flags */
    .nominal_reading = (30 << 1), /* Nominal reading */
    .normal_max = (50 << 1), /* Normal maximum */
    .normal_min = (20 << 1), /* Normal minimum */
    .sensor_max_reading = 0xFF, /* Sensor Maximum reading */
    .sensor_min_reading = 0x00, /* Sensor Minimum reading */
    .upper_nonrecover_thr = (75 << 1), /* Upper non-recoverable Threshold */
    .upper_critical_thr = (65 << 1), /* Upper critical Threshold */
    .upper_noncritical_thr = (55 << 1), /* Upper non critical Threshold */
    .lower_nonrecover_thr = (5 << 1), /* Lower non-recoverable Threshold */
    .lower_critical_thr = (10 << 1), /* Lower critical Threshold */
    .lower_noncritical_thr = (20 << 1), /* Lower non-critical Threshold */
    .pos_thr_hysteresis = 2, /* positive going Threshold hysteresis value */
    .neg_thr_hysteresis = 2, /* negative going Threshold hysteresis value */
    .reserved1 = 0x00, /* reserved */
    .reserved2 = 0x00, /* reserved */
    .OEM = 0x00, /* OEM reserved */
    .IDtypelen = 0xc0 | STR_SIZE("TEMP CLK SWITCH"), /* 8 bit ASCII, number of bytes */
    .IDstring = "TEMP CLK SWITCH" /*  sensor string */
};

const SDR_type_01h_t SDR_LM75_DCDC = {

    .hdr.recID_LSB = NUM_SDR_LM75_DCDC,
    .hdr.recID_MSB = 0x00,
    .hdr.SDRversion = 0x51,
    .hdr.rectype = TYPE_01,
    .hdr.reclength = sizeof(SDR_type_01h_t) - sizeof(SDR_entry_hdr_t),

    .ownerID = 0x00, /* i2c address, -> SDR_Init */
    .ownerLUN = 0x00, /* sensor owner LUN */
    .sensornum = NUM_SDR_LM75_DCDC, /* sensor number */

    /* record body bytes */
    .entityID = 0xC1, /* entity id: AMC Module */
    .entityinstance = 0x00, /* entity instance -> SDR_Init */
    .sensorinit = 0x7f, /* init: event generation + scanning enabled */
    .sensorcap = 0x68, /* capabilities: auto re-arm,*/
    .sensortype = SENSOR_TYPE_TEMPERATURE, /* sensor type */
    .event_reading_type = 0x01, /* sensor reading*/
    .assertion_event_mask = { 0xFF, /* LSB assert event mask: 3 bit value */
                              0x0F }, /* MSB assert event mask */
    .deassertion_event_mask = { 0xFF, /* LSB deassert event mask: 3 bit value */
                                0x0F }, /* MSB deassert event mask */
    .readable_threshold_mask = 0x3F, /* LSB: readabled Threshold mask: all thresholds are readabled:  */
    .settable_threshold_mask = 0x3F, /* MSB: setabled Threshold mask: all thresholds are setabled: */
    .sensor_units_1 = 0x00, /* sensor units 1 :*/
    .sensor_units_2 = 0x01, /* sensor units 2 :*/
    .sensor_units_3 = 0x00, /* sensor units 3 :*/
    .linearization = 0x00, /* Linearization */
    .M = 5, /* M */
    .M_tol = 0x00, /* M - Tolerance */
    .B = 0x00, /* B */
    .B_accuracy = 0x00, /* B - Accuracy */
    .acc_exp_sensor_dir = 0x00, /* Sensor direction */
    .Rexp_Bexp = 0xF0, /* R-Exp , B-Exp */
    .analog_flags = 0x03, /* Analogue characteristics flags */
    .nominal_reading = (30 << 1), /* Nominal reading */
    .normal_max = (50 << 1), /* Normal maximum */
    .normal_min = (20 << 1), /* Normal minimum */
    .sensor_max_reading = 0xFF, /* Sensor Maximum reading */
    .sensor_min_reading = 0x00, /* Sensor Minimum reading */
    .upper_nonrecover_thr = (75 << 1), /* Upper non-recoverable Threshold */
    .upper_critical_thr = (65 << 1), /* Upper critical Threshold */
    .upper_noncritical_thr = (55 << 1), /* Upper non critical Threshold */
    .lower_nonrecover_thr = (5 << 1), /* Lower non-recoverable Threshold */
    .lower_critical_thr = (10 << 1), /* Lower critical Threshold */
    .lower_noncritical_thr = (20 << 1), /* Lower non-critical Threshold */
    .pos_thr_hysteresis = 2, /* positive going Threshold hysteresis value */
    .neg_thr_hysteresis = 2, /* negative going Threshold hysteresis value */
    .reserved1 = 0x00, /* reserved */
    .reserved2 = 0x00, /* reserved */
    .OEM = 0x00, /* OEM reserved */
    .IDtypelen = 0xc0 | STR_SIZE("TEMP DCDC"), /* 8 bit ASCII, number of bytes */
    .IDstring = "TEMP DCDC" /*  sensor string */
};

const SDR_type_01h_t SDR_LM75_RAM = {

    .hdr.recID_LSB = NUM_SDR_LM75_RAM,
    .hdr.recID_MSB = 0x00,
    .hdr.SDRversion = 0x51,
    .hdr.rectype = TYPE_01,
    .hdr.reclength = sizeof(SDR_type_01h_t) - sizeof(SDR_entry_hdr_t),

    .ownerID = 0x00, /* i2c address, -> SDR_Init */
    .ownerLUN = 0x00, /* sensor owner LUN */
    .sensornum = NUM_SDR_LM75_RAM, /* sensor number */

    /* record body bytes */
    .entityID = 0xC1, /* entity id: AMC Module */
    .entityinstance = 0x00, /* entity instance -> SDR_Init */
    .sensorinit = 0x7f, /* init: event generation + scanning enabled */
    .sensorcap = 0x68, /* capabilities: auto re-arm,*/
    .sensortype = SENSOR_TYPE_TEMPERATURE, /* sensor type */
    .event_reading_type = 0x01, /* sensor reading*/
    .assertion_event_mask = { 0xFF, /* LSB assert event mask: 3 bit value */
                              0x0F }, /* MSB assert event mask */
    .deassertion_event_mask = { 0xFF, /* LSB deassert event mask: 3 bit value */
                                0x0F }, /* MSB deassert event mask */
    .readable_threshold_mask = 0x3F, /* LSB: readabled Threshold mask: all thresholds are readabled:  */
    .settable_threshold_mask = 0x3F, /* MSB: setabled Threshold mask: all thresholds are setabled: */
    .sensor_units_1 = 0x00, /* sensor units 1 :*/
    .sensor_units_2 = 0x01, /* sensor units 2 :*/
    .sensor_units_3 = 0x00, /* sensor units 3 :*/
    .linearization = 0x00, /* Linearization */
    .M = 5, /* M */
    .M_tol = 0x00, /* M - Tolerance */
    .B = 0x00, /* B */
    .B_accuracy = 0x00, /* B - Accuracy */
    .acc_exp_sensor_dir = 0x00, /* Sensor direction */
    .Rexp_Bexp = 0xF0, /* R-Exp , B-Exp */
    .analog_flags = 0x03, /* Analogue characteristics flags */
    .nominal_reading = (30 << 1), /* Nominal reading */
    .normal_max = (50 << 1), /* Normal maximum */
    .normal_min = (20 << 1), /* Normal minimum */
    .sensor_max_reading = 0xFF, /* Sensor Maximum reading */
    .sensor_min_reading = 0x00, /* Sensor Minimum reading */
    .upper_nonrecover_thr = (75 << 1), /* Upper non-recoverable Threshold */
    .upper_critical_thr = (65 << 1), /* Upper critical Threshold */
    .upper_noncritical_thr = (55 << 1), /* Upper non critical Threshold */
    .lower_nonrecover_thr = (5 << 1), /* Lower non-recoverable Threshold */
    .lower_critical_thr = (10 << 1), /* Lower critical Threshold */
    .lower_noncritical_thr = (20 << 1), /* Lower non-critical Threshold */
    .pos_thr_hysteresis = 2, /* positive going Threshold hysteresis value */
    .neg_thr_hysteresis = 2, /* negative going Threshold hysteresis value */
    .reserved1 = 0x00, /* reserved */
    .reserved2 = 0x00, /* reserved */
    .OEM = 0x00, /* OEM reserved */
    .IDtypelen = 0xc0 | STR_SIZE("TEMP RAM"), /* 8 bit ASCII, number of bytes */
    .IDstring = "TEMP RAM" /* sensor string */
};

sensor_t sensor_array[NUM_SDR]  = {
    /* Entry record */
    { .type = TYPE_12, .sdr = (void *) &SDR0, .sdr_length = sizeof(SDR0), .task_handle = NULL, .diag_devID = NO_DIAG },

    /* AMC Hotswap */
    { .type = TYPE_02, .sdr = (void *) &SDR_HOT_SWAP,  .sdr_length = sizeof(SDR_HOT_SWAP),  .task_handle = &vTaskHotSwap_Handle, .diag_devID = NO_DIAG },
#ifdef MODULE_RTM
    { .type = TYPE_02, .sdr = (void *) &SDR_HOT_SWAP,  .sdr_length = sizeof(SDR_HOT_SWAP),  .task_handle = &vTaskHotSwap_Handle, .diag_devID = NO_DIAG },
#endif

    /* FMC1 Voltage */
    { .type = TYPE_01, .sdr = (void *) &SDR_FMC1_12V,  .sdr_length = sizeof(SDR_FMC1_12V),  .task_handle = &vTaskINA220_Handle,  .diag_devID = FMC1_12V_DEVID,  .slave_addr = 0x40 },
    { .type = TYPE_01, .sdr = (void *) &SDR_FMC1_VADJ, .sdr_length = sizeof(SDR_FMC1_VADJ), .task_handle = &vTaskINA220_Handle,  .diag_devID = FMC1_VADJ_DEVID, .slave_addr = 0x41 },
    { .type = TYPE_01, .sdr = (void *) &SDR_FMC1_P3V3, .sdr_length = sizeof(SDR_FMC1_P3V3), .task_handle = &vTaskINA220_Handle,  .diag_devID = FMC1_P3V3_DEVID, .slave_addr = 0x43 },

    /* FMC1 Current */
    { .type = TYPE_01, .sdr = (void *) &SDR_FMC1_12V_CURR,  .sdr_length = sizeof(SDR_FMC1_12V_CURR),  .task_handle = &vTaskINA220_Handle,  .diag_devID = FMC1_12V_CURR_DEVID,  .slave_addr = 0x40 },
    { .type = TYPE_01, .sdr = (void *) &SDR_FMC1_VADJ_CURR, .sdr_length = sizeof(SDR_FMC1_VADJ_CURR), .task_handle = &vTaskINA220_Handle,  .diag_devID = FMC1_VADJ_CURR_DEVID, .slave_addr = 0x41 },
    { .type = TYPE_01, .sdr = (void *) &SDR_FMC1_P3V3_CURR, .sdr_length = sizeof(SDR_FMC1_P3V3_CURR), .task_handle = &vTaskINA220_Handle,  .diag_devID = FMC1_P3V3_CURR_DEVID, .slave_addr = 0x43 },

    /* FMC2 Voltage */
    { .type = TYPE_01, .sdr = (void *) &SDR_FMC2_12V,  .sdr_length = sizeof(SDR_FMC2_12V),  .task_handle = &vTaskINA220_Handle,  .diag_devID = FMC2_12V_DEVID,  .slave_addr = 0x45 },
    { .type = TYPE_01, .sdr = (void *) &SDR_FMC2_VADJ, .sdr_length = sizeof(SDR_FMC2_VADJ), .task_handle = &vTaskINA220_Handle,  .diag_devID = FMC2_VADJ_DEVID, .slave_addr = 0x42 },
    { .type = TYPE_01, .sdr = (void *) &SDR_FMC2_P3V3, .sdr_length = sizeof(SDR_FMC2_P3V3), .task_handle = &vTaskINA220_Handle,  .diag_devID = FMC2_P3V3_DEVID, .slave_addr = 0x44 },

    /* FMC2 Current  */
    { .type = TYPE_01, .sdr = (void *) &SDR_FMC2_12V_CURR,  .sdr_length = sizeof(SDR_FMC2_12V_CURR),  .task_handle = &vTaskINA220_Handle,  .diag_devID = FMC2_12V_CURR_DEVID,  .slave_addr = 0x45 },
    { .type = TYPE_01, .sdr = (void *) &SDR_FMC2_VADJ_CURR, .sdr_length = sizeof(SDR_FMC2_VADJ_CURR), .task_handle = &vTaskINA220_Handle,  .diag_devID = FMC2_VADJ_CURR_DEVID, .slave_addr = 0x42 },
    { .type = TYPE_01, .sdr = (void *) &SDR_FMC2_P3V3_CURR, .sdr_length = sizeof(SDR_FMC2_P3V3_CURR), .task_handle = &vTaskINA220_Handle,  .diag_devID = FMC2_P3V3_CURR_DEVID, .slave_addr = 0x44 },

    /* Temperature Sensors */
    { .type = TYPE_01, .sdr = (void *) &SDR_LM75_uC,           .sdr_length = sizeof(SDR_LM75_uC),           .task_handle = &vTaskLM75_Handle,    .diag_devID = NO_DIAG,         .slave_addr = 0x4C },
    { .type = TYPE_01, .sdr = (void *) &SDR_LM75_CLOCK_SWITCH, .sdr_length = sizeof(SDR_LM75_CLOCK_SWITCH), .task_handle = &vTaskLM75_Handle,    .diag_devID = NO_DIAG,         .slave_addr = 0x4D },
    { .type = TYPE_01, .sdr = (void *) &SDR_LM75_DCDC,         .sdr_length = sizeof(SDR_LM75_DCDC),         .task_handle = &vTaskLM75_Handle,    .diag_devID = DCDC_TEMP_DEVID, .slave_addr = 0x4E },
    { .type = TYPE_01, .sdr = (void *) &SDR_LM75_RAM,          .sdr_length = sizeof(SDR_LM75_RAM),          .task_handle = &vTaskLM75_Handle,    .diag_devID = RAM_TEMP_DEVID,  .slave_addr = 0x4F }
};
