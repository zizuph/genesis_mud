/*
 * Filename:    forged_armour.c
 * Description: This is the base file for all forged armours,
 *              it contains all the functions needed to configure
 *              the armour you want to forge.
 *              To use it just inherit it, and in your create_armour
 *              funtion you call the functions needed.
 *
 * Copyright (c) Jan, 2003 by Boron aka. Daniel W. Mathiasen
 */

static string ForgedName;
static string* Ingridients;

public nomask string
query_forged_name()
{
    return ForgedName;
}

public nomask void
set_forged_name(string str)
{
    ForgedName = str;
}

public nomask string*
query_ingridients()
{
    return Ingridients;
}

public nomask void
set_ingridients(string *str)
{
    Ingridients += ({ str });
}
