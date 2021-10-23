/*
 * globals.h
 *
 *  Created on: Oct 19, 2021
 *      Author: keith
 */

#ifndef EXTERNS_H_
#define EXTERNS_H_

#include <mutex>
#include "Soupline.h"
#include "Auditor.h"

//Tells the compiler that these globals are defined somewhere
//in the project.  The linker finds them.
extern Soupline msl;
extern std::mutex soup_mutex;
extern std::mutex drink_mutex;
extern Auditor auditor;

#endif /* EXTERNS_H_ */
