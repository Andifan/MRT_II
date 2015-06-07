/*
 * tuersteuerung.h
 *
 *  Created on: 06.06.2015
 *      Author: mrt
 */

#ifndef TUERSTEUERUNG_H_
#define TUERSTEUERUNG_H_

bool tuer_oeffnen();

bool tuer_auf(double zeit);

bool tuer_schliessen();

bool steuerungsalgorithmus();

void signalverarbeitung();



#endif /* TUERSTEUERUNG_H_ */
