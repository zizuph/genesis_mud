/*
 *  local.h
 *
 *  This is the local for the Temple of Mithas.
 *
 *  Created by Carnak, January 2016
 */
 
#include "/d/Krynn/common/clock/clock.h"

#ifndef TEMPLE_DEF
#define TEMPLE_DEF

#define C_QUEST "_quest_of_chislev"

#define TDIR    "/d/Ansalon/goodlund/nethosak/chislev_temple/"
#define TLOG    TDIR + "log/"
#define TNPC    TDIR + "living/"
#define TOBJ    TDIR + "obj/"
#define TWEP    TOBJ + "weapon/"

#endif TEMPLE_DEF

string
tod_desc()
{
    string str;
    switch (GET_TIME_STRING)
    {
        case MIDNIGHT:
        str = "It's the middle of the night. Faint light from the two "+
        "moons, Lunitari and Solinari, enters through the open hatch "+
        "in the roof. ";
            break;
            
        case NIGHT:
        str = "Night has fallen. The candelabras spread a warm light from "+
        "the corners of the temple, the shadows dancing as the light "+
        "flickers. ";
            break;
            
        case EARLY_MORNING:
        str = "Bright colours from the rising sun disperse the dark of "+
        "night. ";
        case MORNING:
        str = "The bright morning sun shines down into the temple. ";
            break;
            
        case EVENING:
        str = "The sun's rays are fading from view as the sun sinks " + 
        "below the horizon. The candelabras gentle glow blends with "+
        "the sun. ";
            break;
            
        case NOON:
        str = "The noon sun lights up the corners of the temple. ";
            break;
            
        case AFTERNOON:
        str = "The afternoon sun fills the temple with a pleasant "+
        "light. ";
            break;
      
    }
    return str;
}


string
season_desc()
{
    string str;
    switch (GET_SEASON)
    {
        case SPRING:
        str = "A mild spring breeze blows through the hatch, removing " +
        "some of the chill of winter. ";
            break;
            
        case SUMMER:
        str = "A warm breeze blows through the hatch, giving you no " + 
        "relief from the summer heat. ";
            break;
            
        case AUTUMN:
        str = "A cool wind blows through the hatch, reminding you that " +
        "winter is not far away. ";
            break;
            
        case WINTER:
        str = "A cold breeze blows through the hatch, chilling your bones. ";  
            break;
    }
    return str;
}


string
sleep_desc()
{
    string str;
    switch (GET_TIME_STRING)
    {
        case MIDNIGHT:
        case NIGHT:
        str = "It is night and the temple is dead quiet, a faint "+
        "light seeps in from the south, allowing you to barely "+
        "perceive your surroundings.\n";
            break;
            
        case EARLY_MORNING:
        case MORNING:
        case EVENING:
        case NOON:
        case AFTERNOON:
        str = "The candles situated on the tables in the temple "+
        "study flicker to and fro, forcing the shadows in the "+
        "vicinity to dance to their will.\n";
            break;
      
    }
    return str;
}