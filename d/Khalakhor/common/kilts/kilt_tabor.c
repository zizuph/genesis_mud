/*
 * kilt_tabor.c
 *
 * A kilt bearing the tartan of clan tabor.
 *
 * Zima - March 14, 1998
 */
#pragma strict_types
  
inherit "/d/Khalakhor/std/arm/kilt_base";
inherit "/lib/keep";
 
public void
create_kilt()
{
    hunting = "black";
    colours = ({"blue", "white"});
    clan = "Clan Tabor";
}
