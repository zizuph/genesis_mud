/*
 * /d/Gondor/morgul/obj/platemail_unique.c
 *
 * This platemail is a unique version of /d/Gondor/morgul/obj/platemail.c
 * It is used to armour the npcs that get killed for the magical platemail
 * a lot (with everything needed to control the number of magical
 * platemails in the game.)
 *
 * Stern, 21-apr-2000
 */

inherit "/d/Gondor/morgul/obj/platemail";


void
create_armour() 
{
    ::create_armour();
    /* reduce the chance of recovery */
    if (random(1) )
    {
        set_may_not_recover();
    }
}


