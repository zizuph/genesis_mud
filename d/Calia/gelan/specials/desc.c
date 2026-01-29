/* 	this is a special file of the town Gelan 
 
    coder(s):   Deinonychus
 
    history:    21. 1.93    created                         Deinonychus
 
    purpose:	holding descriptions for some buildings in Gelan 
 
    to do:      none 
    bug:        none known 
*/ 
 
#include "specials.h" 
#include "desc.h" 
 
/* 
 * Function name: desc
 * Description:   returns the description of an object 
 * Arguments:     name of object 
 * Returns:       descriptions of the object
 */ 
 
string 
desc(string str) 
{ 
 
    return desc[str]; 
 
} 
