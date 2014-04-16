/*
 * This header contains definitions of
 * keys for compilation ( debugging options )
 * 
 * This header MUST be included in every file of this project!
 * */
#ifndef _BUILD_H_
#define _BUILD_H_

#define _NOPE_   	0
#define _LIGHT_  	1
#define _DETAIL_ 	2
#define _HEAVY_  	3

// prints debug information to cerr
#define _DEBUG_  _LIGHT_ 
////////////////////////////////////////////////////////////////////////
#include <iostream>


#if ((_DEBUG_) != (_NOPE_))
	#define debug(msg) std::cerr << msg
#else
	#define debug(msg)
#endif
////////////////////////////////////////////////////////////////////////

#if ((_DEBUG_) == (_DETAIL_))
	#define debug_detail(msg) debug(msg)
#else
	#define debug_detail(msg)
#endif

#if ((_DEBUG_) == (_HEAVY_))
	#define debug_heavy(msg) debug(msg)
#else
	#define debug_heavy(msg)
#endif

////////////////////////////////////////////////////////////////////////

#endif //_BUILD_H_
