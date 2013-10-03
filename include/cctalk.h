/*
 * Copyright (C) 2013  Jan Dvorak <mordae@anilinux.org>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _CCTALK_H
#define _CCTALK_H 1

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif


/* Available crc modes. */
enum cctalk_crc_mode {
	/* Simple 256-complement, 1 byte checksum after every message. */
	CCTALK_CRC_SIMPLE = 0,

	/* Full CRC-16-CCITT checksum using source address field and one
	 * more byte after every message. */
	CCTALK_CRC_CCITT = 1,
};

/* Known remote methods. */
enum cctalk_method {
	CCTALK_METHOD_RESET_DEVICE = 1,
	CCTALK_METHOD_REQUEST_COMMS_STATUS_VARIABLES = 2,
	CCTALK_METHOD_CLEAR_COMMS_STATUS_VARIABLES = 3,
	CCTALK_METHOD_REQUEST_COMMS_REVISION = 4,
	CCTALK_METHOD_READ_BARCODE_DATA = 129,
	CCTALK_METHOD_REQUEST_INDEXED_HOPPER_DISPENSE_COUNT = 130,
	CCTALK_METHOD_REQUEST_HOPPER_COIN_VALUE = 131,
	CCTALK_METHOD_EMERGENCY_STOP_VALUE = 132,
	CCTALK_METHOD_REQUEST_HOPPER_POLLING_VALUE = 133,
	CCTALK_METHOD_DISPENSE_HOPPER_VALUE = 134,
	CCTALK_METHOD_SET_ACCEPT_LIMIT = 135,
	CCTALK_METHOD_STORE_ENCRYPTION_CODE = 136,
	CCTALK_METHOD_SWITCH_ENCRYPTION_CODE = 137,
	CCTALK_METHOD_FINISH_FIRMWARE_UPGRADE = 138,
	CCTALK_METHOD_BEGIN_FIRMWARE_UPGRADE = 139,
	CCTALK_METHOD_UPLOAD_FIRMWARE = 140,
	CCTALK_METHOD_REQUEST_FIRMWARE_UPGRADE_CAPABILITY = 141,
	CCTALK_METHOD_FINISH_BILL_TABLE_UPGRADE = 142,
	CCTALK_METHOD_BEGIN_BILL_TABLE_UPGRADE = 143,
	CCTALK_METHOD_UPLOAD_BILL_TABLES = 144,
	CCTALK_METHOD_REQUEST_CURRENCY_REVISION = 145,
	CCTALK_METHOD_OPERATE_BIDIRECTIONAL_MOTORS = 146,
	CCTALK_METHOD_PERFORM_STACKER_CYCLE = 147,
	CCTALK_METHOD_READ_OPTO_VOLTAGES = 148,
	CCTALK_METHOD_REQUEST_INDIVIDUAL_ERROR_COUNTER = 149,
	CCTALK_METHOD_REQUEST_INDIVIDUAL_ACCEPT_COUNTER = 150,
	CCTALK_METHOD_TEST_LAMPS = 151,
	CCTALK_METHOD_REQUEST_BILL_OPERATING_MODE = 152,
	CCTALK_METHOD_MODIFY_BILL_OPERATING_MODE = 153,
	CCTALK_METHOD_ROUTE_BILL = 154,
	CCTALK_METHOD_REQUEST_BILL_POSITION = 155,
	CCTALK_METHOD_REQUEST_COUNTRY_SCALING_FACTOR = 156,
	CCTALK_METHOD_REQUEST_BILL_ID = 157,
	CCTALK_METHOD_MODIFY_BILL_ID = 158,
	CCTALK_METHOD_READ_BUFFERED_BILL_EVENTS = 159,
	CCTALK_METHOD_REQUEST_CIPHER_KEY = 160,
	CCTALK_METHOD_PUMP_RNG = 161,
	CCTALK_METHOD_MODIFY_INHIBIT_AND_OVERRIDE_REGISTERS = 162,
	CCTALK_METHOD_TEST_HOPPER = 163,
	CCTALK_METHOD_ENABLE_HOPPER = 164,
	CCTALK_METHOD_MODIFY_VARIABLE_SET = 165,
	CCTALK_METHOD_REQUEST_HOPPER_STATUS = 166,
	CCTALK_METHOD_DISPENSE_HOPPER_COINS = 167,
	CCTALK_METHOD_REQUEST_HOPPER_DISPENSE_COUNT = 168,
	CCTALK_METHOD_REQUEST_ADDRESS_MODE = 169,
	CCTALK_METHOD_REQUEST_BASE_YEAR = 170,
	CCTALK_METHOD_REQUEST_HOPPER_COIN = 171,
	CCTALK_METHOD_EMERGENCY_STOP = 172,
	CCTALK_METHOD_REQUEST_THERMISTOR_READING = 173,
	CCTALK_METHOD_REQUEST_PAYOUT_FLOAT = 174,
	CCTALK_METHOD_MODIFY_PAYOUT_FLOAT = 175,
	CCTALK_METHOD_REQUEST_ALARM_COUNTER = 176,
	CCTALK_METHOD_HANDHELD_FUNCTION = 177,
	CCTALK_METHOD_REQUEST_BANK_SELECT = 178,
	CCTALK_METHOD_MODIFY_BANK_SELECT = 179,
	CCTALK_METHOD_REQUEST_SECURITY_SETTING = 180,
	CCTALK_METHOD_MODIFY_SECURITY_SETTING = 181,
	CCTALK_METHOD_DOWNLOAD_CALIBRATION_INFO = 182,
	CCTALK_METHOD_UPLOAD_WINDOW_DATA = 183,
	CCTALK_METHOD_REQUEST_COIN_ID = 184,
	CCTALK_METHOD_MODIFY_COIN_ID = 185,
	CCTALK_METHOD_REQUEST_PAYOUT_CAPACITY = 186,
	CCTALK_METHOD_MODIFY_PAYOUT_CAPACITY = 187,
	CCTALK_METHOD_REQUEST_DEFAULT_SORTER_PATH = 188,
	CCTALK_METHOD_MODIFY_DEFAULT_SORTER_PATH = 189,
	CCTALK_METHOD_REQUEST_PAYOUT_STATUS = 190,
	CCTALK_METHOD_KEYPAD_CONTROL = 191,
	CCTALK_METHOD_REQUEST_BUILD_CODE = 192,
	CCTALK_METHOD_REQUEST_FRAUD_COUNTER = 193,
	CCTALK_METHOD_REQUEST_REJECT_COUNTER = 194,
	CCTALK_METHOD_REQUEST_LAST_MODIFICATION_DATE = 195,
	CCTALK_METHOD_REQUEST_CREATION_DATE = 196,
	CCTALK_METHOD_CALCULATE_ROM_CHECKSUM = 197,
	CCTALK_METHOD_COUNTERS_TO_EEPROM = 198,
	CCTALK_METHOD_CONFIGURATION_TO_EEPROM = 199,
	CCTALK_METHOD_UPLOAD_COIN_DATA = 200,
	CCTALK_METHOD_REQUEST_TEACH_STATUS = 201,
	CCTALK_METHOD_TEACH_MODE_CONTROL = 202,
	CCTALK_METHOD_DISPLAY_CONTROL = 203,
	CCTALK_METHOD_METER_CONTROL = 204,
	CCTALK_METHOD_REQUEST_AUDIT_INFORMATION_BLOCK = 205,
	CCTALK_METHOD_EMPTY_PAYOUT = 206,
	CCTALK_METHOD_REQUEST_PAYOUT_ABSOLUTE_COUNT = 207,
	CCTALK_METHOD_MODIFY_PAYOUT_ABSOLUTE_COUNT = 208,
	CCTALK_METHOD_REQUEST_SORTER_PATHS = 209,
	CCTALK_METHOD_MODIFY_SORTER_PATHS = 210,
	CCTALK_METHOD_POWER_MANAGEMENT_CONTROL = 211,
	CCTALK_METHOD_REQUEST_COIN_POSITION = 212,
	CCTALK_METHOD_REQUEST_OPTION_FLAGS = 213,
	CCTALK_METHOD_WRITE_DATA_BLOCK = 214,
	CCTALK_METHOD_READ_DATA_BLOCK = 215,
	CCTALK_METHOD_REQUEST_DATA_STORAGE_AVAILABILITY = 216,
	CCTALK_METHOD_REQUEST_PAYOUT_HIGH_LOW_STATUS = 217,
	CCTALK_METHOD_ENTER_PIN_NUMBER = 218,
	CCTALK_METHOD_ENTER_NEW_PIN_NUMBER = 219,
	CCTALK_METHOD_ONE_SHOT_CREDIT = 220,
	CCTALK_METHOD_REQUEST_SORTER_OVERRIDE_STATUS = 221,
	CCTALK_METHOD_MODIFY_SORTER_OVERRIDE_STATUS = 222,
	CCTALK_METHOD_DISPENSE_CHANGE = 223,
	CCTALK_METHOD_DISPENSE_COINS = 224,
	CCTALK_METHOD_REQUEST_ACCEPT_COUNTER = 225,
	CCTALK_METHOD_REQUEST_INSERTION_COUNTER = 226,
	CCTALK_METHOD_REQUEST_MASTER_INHIBIT_STATUS = 227,
	CCTALK_METHOD_MODIFY_MASTER_INHIBIT_STATUS = 228,
	CCTALK_METHOD_READ_BUFFERED_CREDIT_OR_ERROR_CODES = 229,
	CCTALK_METHOD_REQUEST_INHIBIT_STATUS = 230,
	CCTALK_METHOD_MODIFY_INHIBIT_STATUS = 231,
	CCTALK_METHOD_PERFORM_SELF_CHECK = 232,
	CCTALK_METHOD_LATCH_OUTPUT_LINES = 233,
	CCTALK_METHOD_ISSUE_GUARD_CODE = 234,
	CCTALK_METHOD_READ_LAST_CREDIT_OR_ERROR_CODE = 235,
	CCTALK_METHOD_READ_OPTO_STATES = 236,
	CCTALK_METHOD_READ_INPUT_LINES = 237,
	CCTALK_METHOD_TEST_OUTPUT_LINES = 238,
	CCTALK_METHOD_OPERATE_MOTORS = 239,
	CCTALK_METHOD_TEST_SOLENOIDS = 240,
	CCTALK_METHOD_REQUEST_SOFTWARE_REVISION = 241,
	CCTALK_METHOD_REQUEST_SERIAL_NUMBER = 242,
	CCTALK_METHOD_REQUEST_DATABASE_VERSION = 243,
	CCTALK_METHOD_REQUEST_PRODUCT_CODE = 244,
	CCTALK_METHOD_REQUEST_EQUIPMENT_CATEGORY_ID = 245,
	CCTALK_METHOD_REQUEST_MANUFACTURER_ID = 246,
	CCTALK_METHOD_REQUEST_VARIABLE_SET = 247,
	CCTALK_METHOD_REQUEST_STATUS = 248,
	CCTALK_METHOD_REQUEST_POLLING_PRIORITY = 249,
	CCTALK_METHOD_ADDRESS_RANDOM = 250,
	CCTALK_METHOD_ADDRESS_CHANGE = 251,
	CCTALK_METHOD_ADDRESS_CLASH = 252,
	CCTALK_METHOD_ADDRESS_POLL = 253,
	CCTALK_METHOD_SIMPLE_POLL = 254,
	CCTALK_METHOD_FACTORY_SETUP_AND_RESET = 255,
};

/* ccTalk host context for communication over serial line. */
struct cctalk_host {
	/* Serial line descriptor. */
	int fd;

	/* Host identifier. */
	uint8_t id;

	/* Selected CRC mode to send and to expect. */
	enum cctalk_crc_mode crc_mode;

	/* Read/write timeout in milliseconds. */
	int timeout;
};

/* Single message with variable-length payload. */
struct cctalk_message {
	uint8_t destination;
	uint8_t length;
	uint8_t source;
	uint8_t header;
	uint8_t data[0];
} __attribute__((__packed__));


/*
 * Create ccTalk host context using specified serial port.
 *
 * You can freely tune the options in the returned structure
 * before you send any messages.
 */
struct cctalk_host *cctalk_host_new(const char *path);

/* Destroy the ccTalk host context. */
void cctalk_host_free(struct cctalk_host *host);

/* Send message via given ccTalk host. */
int cctalk_send(struct cctalk_host *host, uint8_t destination,
                enum cctalk_method method, size_t length, void *data);

/*
 * Receive single message via given ccTalk host.
 * Returns NULL if no data arrives for more than timeout milliseconds.
 */
struct cctalk_message *cctalk_recv(struct cctalk_host *host);


#ifdef __cplusplus
}
#endif

#endif				/* !_CCTALK_H */
