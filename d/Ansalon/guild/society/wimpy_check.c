/*
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 *
 * Function name: wimp_check
 * Description  : Checks size of player and returns appropriate
 *                wimpy setting on a sliding scale.
 * Arguments    : object who - who to find the setting for
 * Returns      : Appropriate wimpy setting
 */
public int
wimp_check(object who)
{
    int size_char = who->query_average_stat();
    int scale;
 
    switch(size_char)
    {
        case 0..15:
            scale = 72;
            break;
        case 16..30:
            scale = 63;
            break;
        case 31..50:
            scale = 54;
            break;
        case 51..70:
            scale = 45;
            break;
        case 71..90:
            scale = 36;
            break;
        case 91..110:
        default:
            scale = 27;
            break;
/*
        case 111..120:
        case 121..170:
        default:
            scale = 18;
            break;
*/
    }
 
    return scale;
}
