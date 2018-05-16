#ifndef __SI44XX_H
#define __SI44XX_H


#define Tx_LENTH 64
#define Rx_LENTH 64



#define MOD_CW    0
#define MOD_OOK   1
#define MOD_2FSK  2
#define MOD_2GFSK 3
#define MOD_4FSK  4
#define MOD_4GFSK 5

//++++++++++++++++++++++++++
//  Communication settings
//++++++++++++++++++++++++++

#define MAX_CTS_RETRY					2500
#define NIRQ_TIMEOUT					10000


//-----------------------------------------------------------------------------
//	Commands
//-----------------------------------------------------------------------------

// Boot Commands
#define CMD_POWER_UP							  0x02
#define CMD_PATCH_IMAGE							0x04 	

// Common Commands
#define CMD_NOP									    0x00 	
#define CMD_PART_INFO							  0x01 	
#define CMD_FUNC_INFO							  0x10 	
#define CMD_SET_PROPERTY						0x11 	
#define CMD_GET_PROPERTY						0x12 	
#define CMD_GPIO_PIN_CFG						0x13 	
#define CMD_FIFO_INFO							  0x15 	
#define CMD_GET_INT_STATUS					0x20 	
#define CMD_REQUEST_DEVICE_STATE		0x33 	
#define CMD_CHANGE_STATE						0x34 	
#define CMD_READ_CMD_BUFF						0x44 	
#define CMD_FRR_A_READ							0x50 	
#define CMD_FRR_B_READ							0x51 	
#define CMD_FRR_C_READ							0x53 	
#define CMD_FRR_D_READ							0x57 	
#define CMD_WRITE_TX_FIFO						0x66 	
#define CMD_READ_RX_FIFO						0x77 	
#define CMD_GET_ADC_READING					0x14		
#define CMD_PACKET_INFO							0x16 	
#define CMD_IRCAL								    0x17 	
#define CMD_PROTOCOL_CFG						0x18 	
#define CMD_GET_PH_STATUS						0x21 	
#define CMD_GET_MODEM_STATUS				0x22 	
#define CMD_GET_CHIP_STATUS					0x23 	
#define CMD_RX_HOP								  0x36 	

// Tx Commands
#define CMD_START_TX							  0x31 	

// Rx Commands
#define CMD_START_RX							  0x32 	

// Debug Commands


//-----------------------------------------------------------------------------
//   Properties
//-----------------------------------------------------------------------------

#define PROP_GLOBAL_GROUP						          0x00
#define PROP_GLOBAL_XO_TUNE			        			0x00 	
#define PROP_GLOBAL_CLK_CFG		        				0x01 	
#define PROP_GLOBAL_LOW_BATT_THRESH       		0x02 	
#define PROP_GLOBAL_CONFIG				        		0x03 	
#define PROP_GLOBAL_WUT_CONFIG        				0x04 	
#define PROP_GLOBAL_WUT_M_15_8	        			0x05 	
#define PROP_GLOBAL_WUT_M_7_0	        				0x06 	
#define PROP_GLOBAL_WUT_R					            0x07 	
#define PROP_GLOBAL_WUT_LDC				      	  	0x08 	
#define PROP_GLOBAL_WUT_CAL       						0x09 	

#define PROP_INT_CTL_GROUP			        			0x01
#define PROP_INT_CTL_ENABLE	        					0x00 	
#define PROP_INT_CTL_PH_ENABLE        				0x01 	
#define PROP_INT_CTL_MODEM_ENABLE       			0x02 	
#define PROP_INT_CTL_CHIP_ENABLE	        		0x03 	

#define PROP_FRR_CTL_GROUP			         			0x02
#define PROP_FRR_CTL_A_MODE			         			0x00 	
#define PROP_FRR_CTL_B_MODE			        			0x01 	
#define PROP_FRR_CTL_C_MODE		        				0x02 	
#define PROP_FRR_CTL_D_MODE		        				0x03

#define PROP_PREAMBLE_GROUP			        			0x10 	
#define PROP_PREAMBLE_TX_LENGTH			        	0x00 	
#define PROP_PREAMBLE_CONFIG_STD_1	    			0x01 	
#define PROP_PREAMBLE_CONFIG_NSTD		      		0x02 	
#define PROP_PREAMBLE_CONFIG_STD_2	    			0x03 	
#define PROP_PREAMBLE_CONFIG				        	0x04 	
#define PROP_PREAMBLE_PATTERN_31_24	    			0x05 	
#define PROP_PREAMBLE_PATTERN_23_16	    			0x06 	
#define PROP_PREAMBLE_PATTERN_15_8	      		0x07 	
#define PROP_PREAMBLE_PATTERN_7_0			      	0x08 	
#define PROP_PREAMBLE_POSTAMBLE_CONFIG	  		0x09 	
#define PROP_PREAMBLE_POSTAMBLE_PATTERN_31_24	0x0A 	
#define PROP_PREAMBLE_POSTAMBLE_PATTERN_23_16	0x0B 	
#define PROP_PREAMBLE_POSTAMBLE_PATTERN_15_8	0x0C 	
#define PROP_PREAMBLE_POSTAMBLE_PATTERN_7_0		0x0D 	

#define PROP_SYNC_GROUP						    	      0x11
#define PROP_SYNC_CONFIG					    	      0x00 	
#define PROP_SYNC_BITS_31_24		    			    0x01 	
#define PROP_SYNC_BITS_23_16			    		    0x02 	
#define PROP_SYNC_BITS_15_8					    	    0x03 	
#define PROP_SYNC_BITS_7_0						        0x04
 	
#define PROP_PKT_GROUP							          0x12
#define PROP_PKT_CRC_CONFIG					        	0x00 	
#define PROP_PKT_WHT_POLY_15_8			    	  	0x01
#define PROP_PKT_WHT_POLY_7_0				    	    0x02
#define PROP_PKT_WHT_SEED_15_8		       		  0x03
#define PROP_PKT_WHT_SEED_7_0			     		    0x04
#define PROP_PKT_WHT_BIT_NUM			    		    0x05
#define PROP_PKT_CONFIG1					          	0x06
#define PROP_PKT_RESERVED_18_7		  	       	0x07
#define PROP_PKT_LEN							            0x08 	
#define PROP_PKT_LEN_FIELD_SOURCE			        0x09 	
#define PROP_PKT_LEN_ADJUST						        0x0A 	
#define PROP_PKT_TX_THRESHOLD			    		    0x0B 	
#define PROP_PKT_RX_THRESHOLD		    			    0x0C 	
#define PROP_PKT_FIELD_1_LENGTH_12_8	    		0x0D 	
#define PROP_PKT_FIELD_1_LENGTH_7_0		    		0x0E 	
#define PROP_PKT_FIELD_1_CONFIG				    	  0x0F 	
#define PROP_PKT_FIELD_1_CRC_CONFIG	    			0x10 	
#define PROP_PKT_FIELD_2_LENGTH_12_8    			0x11 	
#define PROP_PKT_FIELD_2_LENGTH_7_0			    	0x12 	
#define PROP_PKT_FIELD_2_CONFIG			    		  0x13 	
#define PROP_PKT_FIELD_2_CRC_CONFIG		    		0x14 	
#define PROP_PKT_FIELD_3_LENGTH_12_8    			0x15 	
#define PROP_PKT_FIELD_3_LENGTH_7_0	    			0x16 	
#define PROP_PKT_FIELD_3_CONFIG				      	0x17 	
#define PROP_PKT_FIELD_3_CRC_CONFIG	    			0x18 	
#define PROP_PKT_FIELD_4_LENGTH_12_8    			0x19 	
#define PROP_PKT_FIELD_4_LENGTH_7_0			    	0x1A 	
#define PROP_PKT_FIELD_4_CONFIG			    		  0x1B 	
#define PROP_PKT_FIELD_4_CRC_CONFIG			     	0x1C 	
#define PROP_PKT_FIELD_5_LENGTH_12_8		    	0x1D 	
#define PROP_PKT_FIELD_5_LENGTH_7_0			    	0x1E 	
#define PROP_PKT_FIELD_5_CONFIG					      0x1F 	
#define PROP_PKT_FIELD_5_CRC_CONFIG			    	0x20 	
#define PROP_PKT_RX_FIELD_1_LENGTH_12_8	    	0x21 	
#define PROP_PKT_RX_FIELD_1_LENGTH_7_0	  		0x22 	
#define PROP_PKT_RX_FIELD_1_CONFIG			    	0x23 	
#define PROP_PKT_RX_FIELD_1_CRC_CONFIG	  		0x24 	
#define PROP_PKT_RX_FIELD_2_LENGTH_12_8	  		0x25 	
#define PROP_PKT_RX_FIELD_2_LENGTH_7_0	  		0x26 	
#define PROP_PKT_RX_FIELD_2_CONFIG			     	0x27 	
#define PROP_PKT_RX_FIELD_2_CRC_CONFIG	  		0x28 	
#define PROP_PKT_RX_FIELD_3_LENGTH_12_8	  		0x29 	
#define PROP_PKT_RX_FIELD_3_LENGTH_7_0	  		0x2A 	
#define PROP_PKT_RX_FIELD_3_CONFIG			     	0x2B 	
#define PROP_PKT_RX_FIELD_3_CRC_CONFIG	  		0x2C 	
#define PROP_PKT_RX_FIELD_4_LENGTH_12_8	  		0x2D 	
#define PROP_PKT_RX_FIELD_4_LENGTH_7_0	  		0x2E 	
#define PROP_PKT_RX_FIELD_4_CONFIG		    		0x2F 	
#define PROP_PKT_RX_FIELD_4_CRC_CONFIG  			0x30 	
#define PROP_PKT_RX_FIELD_5_LENGTH_12_8	  		0x31 	
#define PROP_PKT_RX_FIELD_5_LENGTH_7_0	   		0x32 	
#define PROP_PKT_RX_FIELD_5_CONFIG		    		0x33 	
#define PROP_PKT_RX_FIELD_5_CRC_CONFIG  			0x34

#define PROP_MODEM_GROUP			          			0x20
#define PROP_MODEM_MOD_TYPE		        				0x00 	
#define PROP_MODEM_MAP_CONTROL	      				0x01 	
#define PROP_MODEM_DATA_RATE_2	      				0x03 	
#define PROP_MODEM_DATA_RATE_1	      				0x04 	
#define PROP_MODEM_DATA_RATE_0	      				0x05 	
#define PROP_MODEM_FREQ_DEV_2		        			0x0A 	
#define PROP_MODEM_FREQ_DEV_1		        			0x0B 	
#define PROP_MODEM_FREQ_DEV_0		        			0x0C 	
#define PROP_MODEM_FREQ_OFFSET_1      				0x0D 	
#define PROP_MODEM_FREQ_OFFSET_0      				0x0E 	
#define PROP_MODEM_AFC_GEAR			         			0x2C 	
#define PROP_MODEM_AFC_WAIT			        			0x2D 	
#define PROP_MODEM_AFC_GAIN_1		        			0x2E 	
#define PROP_MODEM_AFC_GAIN_0		        			0x2F 	
#define PROP_MODEM_AFC_LIMITER_1      				0x30 	
#define PROP_MODEM_AFC_LIMITER_0      				0x30 	
#define PROP_MODEM_AFC_MISC			        			0x32 	
#define PROP_MODEM_AFC_ZIFOFF		        			0x33 	
#define PROP_MODEM_ADC_CTRL				         		0x34
#define PROP_MODEM_FSK4_MAP 			        		0x3F 	
#define PROP_MODEM_ANT_DIV_CONTROL    				0x49 	
#define PROP_MODEM_RSSI_THRESH		      			0x4A 	
#define PROP_MODEM_RSSI_JUMP_THRESH			    	0x4B 	
#define PROP_MODEM_RSSI_CONTROL					      0x4C 	
#define PROP_MODEM_RSSI_CONTROL2		          0x4D 	
#define PROP_MODEM_RSSI_COMP					        0x4E 	
#define PROP_MODEM_RESERVED_20_50				      0x50

#define PROP_MODEM_CHFLT_GROUP					      0x21 	
#define PROP_MODEM_CHFLT_RX1_CHFLT_COE13_7_0  0x00 	
#define PROP_MODEM_CHFLT_RX1_CHFLT_COE12_7_0	0x01 	
#define PROP_MODEM_CHFLT_RX1_CHFLT_COE11_7_0	0x02 	
#define PROP_MODEM_CHFLT_RX1_CHFLT_COE10_7_0	0x03 	
#define PROP_MODEM_CHFLT_RX1_CHFLT_COE9_7_0		0x04 	
#define PROP_MODEM_CHFLT_RX1_CHFLT_COE8_7_0		0x05 	
#define PROP_MODEM_CHFLT_RX1_CHFLT_COE7_7_0		0x06 	
#define PROP_MODEM_CHFLT_RX1_CHFLT_COE6_7_0		0x07 	
#define PROP_MODEM_CHFLT_RX1_CHFLT_COE5_7_0		0x08 	
#define PROP_MODEM_CHFLT_RX1_CHFLT_COE4_7_0		0x09 	
#define PROP_MODEM_CHFLT_RX1_CHFLT_COE3_7_0		0x0A 	
#define PROP_MODEM_CHFLT_RX1_CHFLT_COE2_7_0		0x0B 	
#define PROP_MODEM_CHFLT_RX1_CHFLT_COE1_7_0		0x0C 	
#define PROP_MODEM_CHFLT_RX1_CHFLT_COE0_7_0		0x0D 	
#define PROP_MODEM_CHFLT_RX1_CHFLT_COEM0		  0x0E 	
#define PROP_MODEM_CHFLT_RX1_CHFLT_COEM1	  	0x0F 	
#define PROP_MODEM_CHFLT_RX1_CHFLT_COEM2	   	0x10 	
#define PROP_MODEM_CHFLT_RX1_CHFLT_COEM3		  0x11 	
#define PROP_MODEM_CHFLT_RX2_CHFLT_COE13_7_0	0x12 	
#define PROP_MODEM_CHFLT_RX2_CHFLT_COE12_7_0	0x13 	
#define PROP_MODEM_CHFLT_RX2_CHFLT_COE11_7_0	0x14 	
#define PROP_MODEM_CHFLT_RX2_CHFLT_COE10_7_0	0x15 	
#define PROP_MODEM_CHFLT_RX2_CHFLT_COE9_7_0		0x16 	
#define PROP_MODEM_CHFLT_RX2_CHFLT_COE8_7_0		0x17 	
#define PROP_MODEM_CHFLT_RX2_CHFLT_COE7_7_0		0x18 	
#define PROP_MODEM_CHFLT_RX2_CHFLT_COE6_7_0		0x19 	
#define PROP_MODEM_CHFLT_RX2_CHFLT_COE5_7_0		0x1A 	
#define PROP_MODEM_CHFLT_RX2_CHFLT_COE4_7_0		0x1B 	
#define PROP_MODEM_CHFLT_RX2_CHFLT_COE3_7_0		0x1C 	
#define PROP_MODEM_CHFLT_RX2_CHFLT_COE2_7_0		0x1D 	
#define PROP_MODEM_CHFLT_RX2_CHFLT_COE1_7_0		0x1E 	
#define PROP_MODEM_CHFLT_RX2_CHFLT_COE0_7_0		0x1F 	
#define PROP_MODEM_CHFLT_RX2_CHFLT_COEM0		  0x20 	
#define PROP_MODEM_CHFLT_RX2_CHFLT_COEM1		  0x21 	
#define PROP_MODEM_CHFLT_RX2_CHFLT_COEM2		  0x22 	
#define PROP_MODEM_CHFLT_RX2_CHFLT_COEM3		  0x23 	

#define PROP_PA_GROUP		      		            0x22
#define PROP_PA_MODE							            0x00 	
#define PROP_PA_PWR_LVL							          0x01 	
#define PROP_PA_BIAS_CLKDUTY		        			0x02 	
#define PROP_PA_TC							            	0x03 	
#define PROP_PA_RAMP_EX					          		0x04 	
#define PROP_PA_RAMP_DOWN_DELAY			      		0x05

#define PROP_MATCH_GROUP				          		0x30  	
#define PROP_MATCH_VALUE_1			        			0x00 	
#define PROP_MATCH_MASK_1				          		0x01 	
#define PROP_MATCH_CTRL_1				           		0x02 	
#define PROP_MATCH_VALUE_2			        			0x03 	
#define PROP_MATCH_MASK_2			          			0x04 	
#define PROP_MATCH_CTRL_2			          			0x05 	
#define PROP_MATCH_VALUE_3			        			0x06 	
#define PROP_MATCH_MASK_3				          		0x07 	
#define PROP_MATCH_CTRL_3				           		0x08 	
#define PROP_MATCH_VALUE_4			        			0x09 	
#define PROP_MATCH_MASK_4				          		0x0A 	
#define PROP_MATCH_CTRL_4				          		0x0B 	

#define PROP_FREQ_CONTROL_GROUP			      		0x40
#define PROP_FREQ_CONTROL_INTE			      		0x00 	
#define PROP_FREQ_CONTROL_FRAC_2		      		0x01 	
#define PROP_FREQ_CONTROL_FRAC_1		      		0x02 	
#define PROP_FREQ_CONTROL_FRAC_0		      		0x03 	
#define PROP_FREQ_CONTROL_CHANNEL_STEP_SIZE_1	0x04 	
#define PROP_FREQ_CONTROL_CHANNEL_STEP_SIZE_0	0x05 	
#define PROP_FREQ_CONTROL_W_SIZE			      	0x06 	
#define PROP_FREQ_CONTROL_VCOCNT_RX_ADJ	  		0x07 	

#define PROP_RX_HOP_GROUP						          0x50 	
#define PROP_RX_HOP_CONTROL					         	0x00 	
#define PROP_RX_HOP_TABLE_SIZE				        0x01 	
#define PROP_RX_HOP_TABLE_ENTRY_0				      0x02 	
#define PROP_RX_HOP_TABLE_ENTRY_1		      		0x03 	
#define PROP_RX_HOP_TABLE_ENTRY_2			      	0x04 	
#define PROP_RX_HOP_TABLE_ENTRY_3			      	0x05 	
#define PROP_RX_HOP_TABLE_ENTRY_4			      	0x06 	
#define PROP_RX_HOP_TABLE_ENTRY_5			      	0x07 	
#define PROP_RX_HOP_TABLE_ENTRY_6		      		0x08 	
#define PROP_RX_HOP_TABLE_ENTRY_7		      		0x09 	
#define PROP_RX_HOP_TABLE_ENTRY_8			      	0x0A 	
#define PROP_RX_HOP_TABLE_ENTRY_9			      	0x0B 	
#define PROP_RX_HOP_TABLE_ENTRY_10     				0x0C 	
#define PROP_RX_HOP_TABLE_ENTRY_11	     			0x0D 	
#define PROP_RX_HOP_TABLE_ENTRY_12	      		0x0E 	
#define PROP_RX_HOP_TABLE_ENTRY_13	  		   	0x0F 	
#define PROP_RX_HOP_TABLE_ENTRY_14	     			0x10 	
#define PROP_RX_HOP_TABLE_ENTRY_15	    			0x11 	
#define PROP_RX_HOP_TABLE_ENTRY_16		    		0x12 	
#define PROP_RX_HOP_TABLE_ENTRY_17	    			0x13 	
#define PROP_RX_HOP_TABLE_ENTRY_18		    		0x14 	
#define PROP_RX_HOP_TABLE_ENTRY_19			    	0x15 	
#define PROP_RX_HOP_TABLE_ENTRY_20			      0x16 	
#define PROP_RX_HOP_TABLE_ENTRY_21    				0x17 	
#define PROP_RX_HOP_TABLE_ENTRY_22    				0x18 	
#define PROP_RX_HOP_TABLE_ENTRY_23    				0x19 	
#define PROP_RX_HOP_TABLE_ENTRY_24    				0x1A 	
#define PROP_RX_HOP_TABLE_ENTRY_25	    			0x1B 	
#define PROP_RX_HOP_TABLE_ENTRY_26    				0x1C 	
#define PROP_RX_HOP_TABLE_ENTRY_27	    			0x1D 	
#define PROP_RX_HOP_TABLE_ENTRY_28	    			0x1E 	
#define PROP_RX_HOP_TABLE_ENTRY_29	    			0x1F 	
#define PROP_RX_HOP_TABLE_ENTRY_30		    		0x20 	
#define PROP_RX_HOP_TABLE_ENTRY_31		    		0x21 	
#define PROP_RX_HOP_TABLE_ENTRY_32		     		0x22 	
#define PROP_RX_HOP_TABLE_ENTRY_33		    		0x23 	
#define PROP_RX_HOP_TABLE_ENTRY_34		    		0x24 	
#define PROP_RX_HOP_TABLE_ENTRY_35		    		0x25 	
#define PROP_RX_HOP_TABLE_ENTRY_36		    		0x26 	
#define PROP_RX_HOP_TABLE_ENTRY_37		    		0x27 	
#define PROP_RX_HOP_TABLE_ENTRY_38		    		0x28 	
#define PROP_RX_HOP_TABLE_ENTRY_39		    		0x29 	
#define PROP_RX_HOP_TABLE_ENTRY_40		     		0x2A 	
#define PROP_RX_HOP_TABLE_ENTRY_41		    		0x2B 	
#define PROP_RX_HOP_TABLE_ENTRY_42		    		0x2C 	
#define PROP_RX_HOP_TABLE_ENTRY_43			     	0x2D 	
#define PROP_RX_HOP_TABLE_ENTRY_44    				0x2E 	
#define PROP_RX_HOP_TABLE_ENTRY_45    				0x2F 	
#define PROP_RX_HOP_TABLE_ENTRY_46     				0x30 	
#define PROP_RX_HOP_TABLE_ENTRY_47		    		0x31 	
#define PROP_RX_HOP_TABLE_ENTRY_48			    	0x32 	
#define PROP_RX_HOP_TABLE_ENTRY_49			     	0x33 	
#define PROP_RX_HOP_TABLE_ENTRY_50		    		0x34 	
#define PROP_RX_HOP_TABLE_ENTRY_51		    		0x35 	
#define PROP_RX_HOP_TABLE_ENTRY_52		    		0x36 	
#define PROP_RX_HOP_TABLE_ENTRY_53		    		0x37 	
#define PROP_RX_HOP_TABLE_ENTRY_54		    		0x38 	
#define PROP_RX_HOP_TABLE_ENTRY_55			    	0x39 	
#define PROP_RX_HOP_TABLE_ENTRY_56			    	0x3A 	
#define PROP_RX_HOP_TABLE_ENTRY_57    				0x3B 	
#define PROP_RX_HOP_TABLE_ENTRY_58	    			0x3C 	
#define PROP_RX_HOP_TABLE_ENTRY_59		    		0x3D 	
#define PROP_RX_HOP_TABLE_ENTRY_60			    	0x3E 	
#define PROP_RX_HOP_TABLE_ENTRY_61  	  			0x3F 	
#define PROP_RX_HOP_TABLE_ENTRY_62	  	  		0x40 	
#define PROP_RX_HOP_TABLE_ENTRY_63				    0x41 	
#define CAP_BANK_VALUE    0x4A    // Capacitor bank value for adjusting the XTAL frequency

//-----------------------------------------------------------------------------
// Header File PreProcessor Directive
//-----------------------------------------------------------------------------

#define EZRADIOPRO2_SI4463_B1

#define XO_TUNE 0x11, 0x00, 0x01, 0x00, 0x52

/*%%	Crys_freq(Hz)	Crys_tol(ppm)	IF_mode	High_perf_Ch_Fil	OSRtune	Ch_Fil_Bw_AFC	ANT_DIV	PM_pattern
 	30000000	10	2	1	0	0	0	0
%%	MOD_type	Rsymb(sps)	Fdev(Hz)	RXBW(Hz)	Mancheste	AFC_en	Rsymb_error	Chip-Version
 	2	2400	15000	200000	0	0	0.0	2
%%	RF Freq.(MHz)	API_TC	fhst	inputBW	BERT	RAW_dout	D_source	Hi_pfm_div
 	470	28	0	0	0	0	0	1
*/

#define CENTER_FREQ 470000000
#define XTAL_FREQ 30000000
#define CHANNEL_SPACING 250000
#define CHANNEL_NUMBER 0
#define XTAL_CAP_BANK 0x52
#define MODULATION_TYPE "2FSK"
#define MODULATION_TYPE_VALUE 2
#define MANCHESTER_CODE "Off"
#define MANCHESTER_CODE_VALUE 0
#define DEVIATION 15000
#define DATA_RATE 2400
#define ANTENNA_DIVERSITY "Disabled"
#define ANTENNA_DIVERSITY_VALUE 0


// # WB filter 2 (BW =  51.53 kHz);  NB-filter 2 (BW = 51.53 kHz) 

// Modulation index: 12

// Calculator svn revision 6239

// EZRadio PRO2 modem calculator output header file  modem_params.h

// RF frequency is 470.00 MHz
// Mod type: 2FSK,	DataRate: 2.40 ksps;  FreqDev: 15.00 kHz;  RX BW: 48.00 kHz 

// all for TX in this section:
//// DataRate: 3 API bytes;  NCOMODulus: 4 bytes; FreqDev: 3 bytes, for TX 
//#define MODEM_DATA_RATE_2_14 0x11, 0x20, 0x0A, 0x03,   0x00, 0x09, 0x60, 0x00, 0x2D, 0xC6, 0xC0, 0x00, 0x04, 0x19
//#define MODEM_TX_RAMP_DELAY_5 0x11, 0x20, 0x01, 0x18,   0x01
//// PA ramp time control: 1 byte
//#define PA_TC_5  0x11, 0x22, 0x01, 0x03, 0x1C


//// all for general parameters in both TRX 
//#define MODEM_MOD_TYPE_7 0x11, 0x20, 0x03, 0x00,  0x02, 0x00, 0x07
//#define MODEM_CLKGEN_BAND_5 0x11, 0x20, 0x01, 0x51,   0x0A
//// SYNTH CONTROL GROUP: 7 API bytes, for both TRX 
//#define SYNTH_PFDCP_CPFF_11 0x11, 0x23, 0x07, 0x00, 0x2C, 0x0E, 0x0B, 0x04, 0x0C, 0x73, 0x03
//// FREQ CONTROL GROUP: 8 API bytes,  TRX
//#define FREQ_CONTROL_INTE_12 0x11, 0x40, 0x08, 0x00,  0x3D, 0x0D, 0x55, 0x55, 0x00, 0x00, 0x20,  0xFE  //???470M
////#define FREQ_CONTROL_INTE_12 0x11, 0x40, 0x08, 0x00, 0x38, 0x0E, 0xEE, 0xEE, 0x22, 0x22, 0x20, 0xFF


//// all for RX below:
//// MDM_CTRL: 1 byte,  IF_CONTROL: 1B,  IF_FREQ: 3B,  DECIMATION_CFG: 2B,  for all RX 
//#define MODEM_MDM_CTRL_11 0x11, 0x20, 0x07, 0x19,   0x80, 0x08, 0x03, 0x80, 0x00, 0x30, 0x20
//// BCR: 10 bytes,  for all RX 
//#define MODEM_BCR_OSR_1_14 0x11, 0x20, 0x0A, 0x22,  0x03, 0x0D, 0x00, 0xA7, 0xC6, 0x00, 0x54, 0x02, 0xC2, 0x00
//// AFC: 8 bytes,  for (G)FSK RX 
//#define MODEM_AFC_GEAR_12 0x11, 0x20, 0x08, 0x2C,  0x04, 0x36, 0x80, 0x07, 0x29, 0x91, 0x80, 0x00

//// AGC: 4 bytes,  for all RX 
//#define MODEM_AGC_CONTRL_5 0x11, 0x20, 0x01, 0x35,   0xE2
//#define MODEM_AGC_WINDOW_SIZE_7 0x11, 0x20, 0x03, 0x38,  0x11, 0xAB, 0xAB

//// 4FSK: 5 bytes,  for 4(G)FSK RX 
//#define MODEM_FSK4_GAIN1_9 0x11, 0x20, 0x05, 0x3B,  0x00, 0x1A, 0x32, 0x00, 0x00
//// OOK: 4 bytes, for RX 
//#define MODEM_OOK_PDTC_8 0x11, 0x20, 0x04, 0x40,  0x2B, 0x0C, 0xA4, 0x02
//// raw: 4 bytes, for RX 
//#define MODEM_RAW_SEARCH_8 0x11, 0x20, 0x04, 0x44,  0xD6, 0x83, 0x01, 0xFF
//// AntDiv: 2 bytes, for RX 
//#define MODEM_ANT_DIV_MODE_6 0x11, 0x20, 0x02, 0x48,  0x01, 0x80
//// RSSI_comp: 1 bytes, for RX 
//#define MODEM_RSSI_COMP_5  0x11, 0x20, 0x01, 0x4E, 0x40

//// RX chfil coeff:  WB filter k1=2 (BW=51.5 kHz), NB filter k2=2 (BW=51.5 kHz)
//// MODEM_CHFLT_RX1 GROUP: 18 API bytes,  for all RX 
//#define MODEM_CHFLT_RX1_CHFLT_COE13_7_0_13 0x11, 0x21, 0x09, 0x00,  0xFF, 0xC4, 0x30, 0x7F, 0xF5, 0xB5, 0xB8, 0xDE, 0x05
//#define MODEM_CHFLT_RX1_CHFLT_COE4_7_0_13  0x11, 0x21, 0x09, 0x09,  0x17, 0x16, 0x0C, 0x03, 0x00, 0x15, 0xFF, 0x00, 0x00
//// MODEM_CHFLT_RX2 GROUP: 18 API bytes, 
//#define MODEM_CHFLT_RX2_CHFLT_COE13_7_0_13 0x11, 0x21, 0x09, 0x12,  0xFF, 0xC4, 0x30, 0x7F, 0xF5, 0xB5, 0xB8, 0xDE, 0x05
//#define MODEM_CHFLT_RX2_CHFLT_COE4_7_0_13  0x11, 0x21, 0x09, 0x1B,  0x17, 0x16, 0x0C, 0x03, 0x00, 0x15, 0xFF, 0x00, 0x00


//#define PA_MODE 0x10, 0x00, 0x00, 0x11, 0x22, 0x01, 0x00, 0x08

//#define PA_BIAS_CLKDUTY 0x10, 0x00, 0x00, 0x11, 0x22, 0x01, 0x02, 0x00

/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*///000000000000000

// CONFIGURATION PARAMETERS
#define RADIO_CONFIGURATION_DATA_RADIO_XO_FREQ                     {30000000L}
#define RADIO_CONFIGURATION_DATA_CHANNEL_NUMBER                    {0x00}
#define RADIO_CONFIGURATION_DATA_RADIO_PACKET_LENGTH               {0x07}
#define RADIO_CONFIGURATION_DATA_RADIO_STATE_AFTER_POWER_UP        {0x03}
#define RADIO_CONFIGURATION_DATA_RADIO_DELAY_CNT_AFTER_RESET       {0xF000}

// CONFIGURATION COMMANDS

/*
// Command:                  RF_POWER_UP
// Description:              Command to power-up the device and select the operational mode and functionality.
*/
//#define RF_POWER_UP 0x02, 0x01, 0x00, 0x01, 0xC9, 0xC3, 0x80

//#define RF_GPIO_PIN_CFG 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

////#define RF_GLOBAL_XO_TUNE_2 0x11, 0x00, 0x02, 0x00, 0x52, 0x41
//#define RF_GLOBAL_XO_TUNE_2 0x11, 0x00, 0x01, 0x00, 0x52 	//更改的,不使能内部32KHz RC定时器, 5字节

////#define RF_GLOBAL_CONFIG_6 0x11, 0x00, 0x06, 0x03, 0x60, 0x42, 0x07, 0x0B, 0x22, 0xF6  //原来的
//#define RF_GLOBAL_CONFIG_6 0x11, 0x00, 0x01, 0x03, 0x00  //修改的,不使能Wake-up Timer

//#define RF_INT_CTL_ENABLE_2 0x11, 0x01, 0x02, 0x00, 0x01, 0x38

//#define RF_FRR_CTL_A_MODE_4 0x11, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00

//#define RF_PREAMBLE_CONFIG_1 0x11, 0x10, 0x01, 0x04, 0x31

//#define RF_SYNC_CONFIG_3 0x11, 0x11, 0x03, 0x00, 0x01, 0xB4, 0x2B

//#define RF_PKT_CONFIG1_1 0x11, 0x12, 0x01, 0x06, 0x02

//#define RF_PKT_FIELD_1_CONFIG_1 0x11, 0x12, 0x01, 0x0F, 0x04

//#define RF_MODEM_MOD_TYPE_12 0x11, 0x20, 0x0C, 0x00, 0x03, 0x00, 0x07, 0x00, 0xBB, 0x80, 0x05, 0xC9, 0xC3, 0x80, 0x00, 0x05 //原来的

//#define RF_MODEM_FREQ_DEV_0_1 0x11, 0x20, 0x01, 0x0C, 0x76 //原来的

//#define RF_MODEM_TX_RAMP_DELAY_8 0x11, 0x20, 0x08, 0x18, 0x01, 0x80, 0x08, 0x03, 0x80, 0x00, 0x20, 0x10 //原来的

//#define RF_MODEM_BCR_OSR_1_9 0x11, 0x20, 0x09, 0x22, 0x08, 0x23, 0x00, 0x3E, 0xEA, 0x00, 0x1F, 0x02, 0xC2

//#define RF_MODEM_AFC_GEAR_7 0x11, 0x20, 0x07, 0x2C, 0x04, 0x36, 0x80, 0x03, 0x51, 0xE3, 0x80 //原来的

//#define RF_MODEM_AGC_CONTROL_1 0x11, 0x20, 0x01, 0x35, 0xE2

//#define RF_MODEM_AGC_WINDOW_SIZE_9 0x11, 0x20, 0x09, 0x38, 0x11, 0xFF, 0xFF, 0x00, 0x1A, 0xFF, 0xFF, 0x00, 0x2B

//#define RF_MODEM_OOK_CNT1_11 0x11, 0x20, 0x0B, 0x42, 0xA4, 0x02, 0xD6, 0x83, 0x01, 0x33, 0x01, 0x80, 0xFF, 0x0C, 0x00

//#define RF_MODEM_RSSI_COMP_1 0x11, 0x20, 0x01, 0x4E, 0x40

//#define RF_MODEM_CLKGEN_BAND_1 0x11, 0x20, 0x01, 0x51, 0x0A  //原来的

//#define RF_MODEM_CHFLT_RX1_CHFLT_COE13_7_0_12 0x11, 0x21, 0x0C, 0x00, 0xFF, 0xBA, 0x0F, 0x51, 0xCF, 0xA9, 0xC9, 0xFC, 0x1B, 0x1E, 0x0F, 0x01  //原来的

//#define RF_MODEM_CHFLT_RX1_CHFLT_COE1_7_0_12 0x11, 0x21, 0x0C, 0x0C, 0xFC, 0xFD, 0x15, 0xFF, 0x00, 0x0F, 0xFF, 0xBA, 0x0F, 0x51, 0xCF, 0xA9    //原来的

//#define RF_MODEM_CHFLT_RX2_CHFLT_COE7_7_0_12 0x11, 0x21, 0x0C, 0x18, 0xC9, 0xFC, 0x1B, 0x1E, 0x0F, 0x01, 0xFC, 0xFD, 0x15, 0xFF, 0x00, 0x0F     //原来的

//#define RF_PA_TC_1 0x11, 0x22, 0x01, 0x03, 0x3D

//#define RF_SYNTH_PFDCP_CPFF_7 0x11, 0x23, 0x07, 0x00, 0x2C, 0x0E, 0x0B, 0x04, 0x0C, 0x73, 0x03

//#define RF_FREQ_CONTROL_INTE_8 0x11, 0x40, 0x08, 0x00, 0x38, 0x0D, 0xDD, 0xDD, 0x44, 0x44, 0x20, 0xFE   //原来的

/*------------------------------------------------------------------------*///000000000000000
/*------------------------------------------------------------------------*///000000000000000
#define RF_POWER_UP 0x02, 0x01, 0x00, 0x01, 0xC9, 0xC3, 0x80


#define RF_GPIO_PIN_CFG 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00


//#define RF_GLOBAL_XO_TUNE_2 0x11, 0x00, 0x02, 0x00, 0x52, 0x41
#define RF_GLOBAL_XO_TUNE_2 0x11, 0x00, 0x02, 0x00, 0x52  //更改的,不使能内部32KHz RC定时器, 5字节

//#define RF_GLOBAL_CONFIG_6 0x11, 0x00, 0x06, 0x03, 0x60, 0x42, 0x20, 0x01, 0x22, 0x08
#define RF_GLOBAL_CONFIG_6 0x11, 0x00, 0x01, 0x03, 0x00  //修改的,不使能Wake-up Timer

//#define RF_INT_CTL_ENABLE_2 0x11, 0x01, 0x02, 0x00, 0x05, 0x18  ////关闭发射中断
#define RF_INT_CTL_ENABLE_2 0x11, 0x01, 0x02, 0x00, 0x05, 0x38  //打开发射中断

#define RF_INT_CTL_CHIP_ENABLE_1 0x11, 0x01, 0x01, 0x03, 0x01



#define RF_FRR_CTL_A_MODE_4 0x11, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00


#define RF_PREAMBLE_CONFIG_1 0x11, 0x10, 0x01, 0x04, 0x31


#define RF_SYNC_CONFIG_3 0x11, 0x11, 0x03, 0x00, 0x01, 0xB4, 0x2B


#define RF_PKT_CONFIG1_1 0x11, 0x12, 0x01, 0x06, 0x02


#define RF_PKT_FIELD_1_CONFIG_1 0x11, 0x12, 0x01, 0x0F, 0x04


#define RF_MODEM_MOD_TYPE_12 0x11, 0x20, 0x0C, 0x00, 0x03, 0x00, 0x07, 0x06, 0x1A, 0x80, 0x05, 0xC9, 0xC3, 0x80, 0x00, 0x02


#define RF_MODEM_FREQ_DEV_0_1 0x11, 0x20, 0x01, 0x0C, 0xBB


#define RF_MODEM_TX_RAMP_DELAY_8 0x11, 0x20, 0x08, 0x18, 0x01, 0x80, 0x08, 0x03, 0xC0, 0x00, 0x10, 0x10


#define RF_MODEM_BCR_OSR_1_9 0x11, 0x20, 0x09, 0x22, 0x01, 0xF4, 0x01, 0x06, 0x25, 0x00, 0x83, 0x02, 0xC2


#define RF_MODEM_AFC_GEAR_7 0x11, 0x20, 0x07, 0x2C, 0x04, 0x36, 0x80, 0x0F, 0x1C, 0x4A, 0xC0


#define RF_MODEM_AGC_CONTROL_1 0x11, 0x20, 0x01, 0x35, 0xE2


#define RF_MODEM_AGC_WINDOW_SIZE_9 0x11, 0x20, 0x09, 0x38, 0x11, 0x6D, 0x6D, 0x00, 0x1A, 0xFF, 0xFF, 0x00, 0x2A


#define RF_MODEM_OOK_CNT1_9 0x11, 0x20, 0x09, 0x42, 0xA4, 0x02, 0xD6, 0x83, 0x00, 0x82, 0x01, 0x80, 0xFF


#define RF_MODEM_RSSI_CONTROL_1 0x11, 0x20, 0x01, 0x4C, 0x00


#define RF_MODEM_RSSI_COMP_1 0x11, 0x20, 0x01, 0x4E, 0x40


#define RF_MODEM_CLKGEN_BAND_1 0x11, 0x20, 0x01, 0x51, 0x08


#define RF_MODEM_CHFLT_RX1_CHFLT_COE13_7_0_12 0x11, 0x21, 0x0C, 0x00, 0xFF, 0xBA, 0x0F, 0x51, 0xCF, 0xA9, 0xC9, 0xFC, 0x1B, 0x1E, 0x0F, 0x01


#define RF_MODEM_CHFLT_RX1_CHFLT_COE1_7_0_12 0x11, 0x21, 0x0C, 0x0C, 0xFC, 0xFD, 0x15, 0xFF, 0x00, 0x0F, 0xFF, 0xBA, 0x0F, 0x51, 0xCF, 0xA9


#define RF_MODEM_CHFLT_RX2_CHFLT_COE7_7_0_12 0x11, 0x21, 0x0C, 0x18, 0xC9, 0xFC, 0x1B, 0x1E, 0x0F, 0x01, 0xFC, 0xFD, 0x15, 0xFF, 0x00, 0x0F


#define RF_PA_TC_1 0x11, 0x22, 0x01, 0x03, 0x3D


#define RF_SYNTH_PFDCP_CPFF_7 0x11, 0x23, 0x07, 0x00, 0x2C, 0x0E, 0x0B, 0x04, 0x0C, 0x73, 0x03

#define RF_FREQ_CONTROL_INTE_8 0x11, 0x40, 0x08, 0x00, 0x38, 0x0E, 0xEE, 0xEE, 0x44, 0x44, 0x20, 0xFF
/*------------------------------------------------------------------------*///000000000000000
unsigned char Spi1ReadWrite(unsigned char uchar);
unsigned char bSpi_SendDataNoResp(unsigned char bDataInLength, unsigned char *pbDataIn);
unsigned char bSpi_SendDataGetResp(unsigned char bDataOutLength, unsigned char *pbDataOut);   // Send data, get the response
unsigned char bSpi_SendDataByte(unsigned char bDataIn);      // Send a single byte via SPI

unsigned char bApi_SendCommand(unsigned char bCmdLength, unsigned char *pbCmdData);   // Send a command + data to the chip
unsigned char vApi_WaitforCTS(void);
unsigned char bApi_GetFastResponseRegister(unsigned char bStartReg, unsigned char bNmbrOfRegs, unsigned char * pbRegValues);
unsigned char bApi_GetResponse(unsigned char bRespLength, unsigned char *pbRespData); // Get response from the chip (used after a command)
unsigned char bApi_ReadRxDataBuffer(unsigned char bRxFifoLength, unsigned char *pbRxFifoData);
unsigned char bApi_WriteTxDataBuffer(unsigned char bTxFifoLength, unsigned char *pbTxFifoData);   // Write Tx FIFO
void vSetPAMode(unsigned char bPaMode, unsigned char bModType);
void Si4463_Init(void);

#endif
