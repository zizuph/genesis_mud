/*	/d/Kalad/common/sewers/lizards_lair/obj/treasury_key.c
 *	The key to the treasuryy in the lizards lair.
 */

inherit "/std/key";

void
create_key()
{
    set_adj("black");
    add_adj("iron");
    set_long("This is a small black iron key..\n");
    set_key("fake_lizard_treasury");
}
