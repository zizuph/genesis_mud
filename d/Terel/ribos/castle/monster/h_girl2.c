/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * h_girl1
 *
 * This is a concubine, coded by Vader on 2/16/93
 * Modified by Sorgum 950707
 */

#include "/d/Terel/include/Terel.h"
inherit RIBOS_DIR + "castle/monster/h_girl1";


do_react(string str1, string str2)
{
    command("smile");
    command("french " + str1);
    command("wiggle");
}

