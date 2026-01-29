/*
 * glowing-shield.c
 * Used in npc/refnas.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Ckrik 20190720 Updated to current magic info standards.
 *                Modernized some part of the ugly code.
 * Refactored
 * Tapakah, 07/2021
 */

#pragma strict_types

inherit "/d/Khalakhor/inisi/roke/arm/glowing-armour";

void
create_armour ()
{
  ::create_glowing_armour("shield");
}
