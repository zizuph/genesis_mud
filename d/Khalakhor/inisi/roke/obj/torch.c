/*
 * torch.c
 *
 * Used in nyreese/cadu_shop.c npc/kobold3.c npc/troll.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* a nice torch to light up the tower when solving the scrollquest */

#pragma save_binary
#pragma strict_types

inherit "/std/torch";

void
create_torch()
{
    set_name("torch");
    set_adj("wooden");
    set_short("wooden torch");
    set_long("The torch is made of tar-drenched wood.\n");
    set_pshort("wooden torches");
}
