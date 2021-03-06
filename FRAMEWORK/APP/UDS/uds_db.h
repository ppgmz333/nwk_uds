/*
 * uds_db.h
 *
 *  Created on: 28/09/2017
 *      Author: Patricio Gomez
 */

#ifndef SOURCE_FRAMEWORK_APP_UDS_UDS_DB_H_
#define SOURCE_FRAMEWORK_APP_UDS_UDS_DB_H_

#include "../can_node.h"

//MACRO to get second byte of DID from extra data
#define GET_EXTRA_DID(xdata)		((xdata&0xFF00) >> 8)

//MACRO to get data from extra data
#define GET_DATA(xdata)				(xdata&0x00FF)

//MACRO to join the first byte of DID (SUB) and the second byte of DID (extra data)
#define JOIN_DID(DID1, DID2)		((DID1 << 8)|(DID2))

//Return (internal, not uds db) code of succesful operation
#define SUCESSFUL					0x91

//SID database
typedef enum{
	DiagnosticSessionControl = 0x10,
	ECUReset = 0x11,
	ReadDataByIdentifier = 0x22,
	SecurityAccess = 0x27,
	WriteDataByIdentifier = 0x2E,
	InputOutputControlByIdentifier = 0x2F
}uds_sid_db_t;

//SUB database (Diagnostic Session Control)
typedef enum{
	sub_Default = 0x01,
	sub_Programming = 0x02,
	sub_Extended = 0x03
}Session_sub_db_t;

//SUB database (ECU Reset)
typedef enum{
	sub_HardReset = 0x01
}ECUR_sub_db_t;

//SUB database (Read Data By Identifier)
typedef enum{
	sub_x_axis = 0xFD40,
	sub_y_axis = 0xFD41,
	sub_z_axis = 0xFD42,
	sub_R_led_color = 0xFE50
}RDID_sub_db_t;

//SUB database (Security Access)
typedef enum{
	sub_level_1 = 0x01,
	sub_level_2 = 0x02
}SA_sub_db_t;

//SUB database (Write Data By Identifier)
typedef enum{
	sub_W_led_color = 0xFE50
}WDID_sub_db_t;

//SUB database (Input Output Control By Identifier)
typedef enum{
	sub_led_status = 0xFE51
}IOCID_sub_db_t;

//NRC database
typedef enum{
	serviceNotSupported = 0x11,
	subFunctionNotSupported = 0x12,
	incorrectMessageLengthOrInvalidFormat = 0x13,
	serviceNotSupportedInActiveSession = 0x7E
}nrc_db_t;

//uds answer structure
typedef struct{
	uint8_t answer_length;
	uint8_t SID_status;
	uint8_t SUB_or_DID1;
	uint8_t DID2;
	uint8_t DATA1;
	uint8_t DATA2;
}uds_db_answer_t;

/**
 * @brief Check if RX data is correct
 *
 * Check through the possible scenarios the UDS
 * has, if the received message if valid
 *
 *	param[in] SID
 *	param[in] SUB
 *	param[in] Length
 *
 * @return @c succesful or error code
 */
uint8_t can_control_check_rx(uint8_t SID, uint8_t SUB, uint8_t Length);

/**
 * @brief Set error answer
 *
 * Depending on the status, build the answer indicating
 * that an error ocurred.
 *
 *	param[in] status: error code
 *	param[in] SID
 *
 * @return @c NULL is always returned.
 */
uint8_t can_control_set_error_answer(uint8_t status, uint8_t SID);

/**
 * @brief DSC
 *
 *	param[in] SUB
 *	param[in] Length
 *
 * @return @c succesful or error code
 */
uint8_t f_DSC(uint8_t SUB, uint8_t Length);

/**
 * @brief ECUR
 *
 *	param[in] SUB
 *	param[in] Length
 *
 * @return @c succesful or error code
 */
uint8_t f_ECUR(uint8_t SUB, uint8_t Length);

/**
 * @brief RDID
 *
 *	param[in] SUB
 *	param[in] Length
 *
 * @return @c succesful or error code
 */
uint8_t f_RDID(uint8_t SUB, uint8_t Length);

/**
 * @brief SA
 *
 *	param[in] SUB
 *	param[in] Length
 *
 * @return @c succesful or error code
 */
uint8_t f_SA(uint8_t SUB, uint8_t Length);

/**
 * @brief WDID
 *
 *	param[in] SUB
 *	param[in] Length
 *
 * @return @c succesful or error code
 */
uint8_t f_WDID(uint8_t SUB, uint8_t Length);

/**
 * @brief IOCID
 *
 *	param[in] SUB
 *	param[in] Length
 *
 * @return @c succesful or error code
 */
uint8_t f_IOCID(uint8_t SUB, uint8_t Length);


#endif /* SOURCE_FRAMEWORK_APP_UDS_UDS_DB_H_ */
