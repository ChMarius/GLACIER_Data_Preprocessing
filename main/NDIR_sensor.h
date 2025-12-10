#pragma once

float NDIR_gas_reading(float active_raw, float reference_raw, float cal_cons);   
float multi_sample_averaging(uint8_t channel, uint8_t sensor);