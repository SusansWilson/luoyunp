//
// Copyright (C) 2002~2005 by Yuking
// yuking_net@sohu.com
// Copyright (C) 2010~2015 by CSSlayer
// wengxt@gmail.com
//
// This library is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; either version 2.1 of the
// License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; see the file COPYING. If not,
// see <http://www.gnu.org/licenses/>.
//

#ifndef _ERRORHANDLER_H
#define _ERRORHANDLER_H

/* ***********************************************************
// Consts
// *********************************************************** */
#ifndef SIGUNUSED
#define SIGUNUSED 29
#endif
/* ***********************************************************
// Data structures
// *********************************************************** */

/* ***********************************************************
// Functions
// *********************************************************** */

//
// Set Posix Signal Handler
//
//
void SetMyExceptionHandler(void);

//
// Process Posix signal
//
void OnException(int signo);

#endif
