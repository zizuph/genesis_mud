/*
 * File         : /d/Genesis/start/hobbit/obj/board.c
 * Creator      : Seaweed - Site
 * Copyright    : Copyright (C) 1999, Joakim Larsson
 * Date         : 3/14/1999
 * Related Files: 
 * Purpose      : 
 *     This is the hobbit startlocation board.
 * Todo         : 
 *      * - nothing
 *
 * Modifications:
 *     N.B. This file is generated from templates hosted elsewhere and
 *     if someone corrects something in this file, please mail Seaweed
 * 
 */

/* directives */
#pragma strict_types
/* inherits */
inherit "/std/board";
/* includes */
#include <stdproperties.h> 
#include <macros.h> 
#include <std.h>
#include "../hobbit.h"
/* defines */

/* prototypes */

/* globals */

void
create_board()
{
    set_long(
    "A plank board madrassed with skin filled with a cotton like " +
    "material works as the village board where village inhabitants " +
    "and visitors can express their opinion about anyting. Even " +
    "though the free word is valued high here one should remember " +
    "that notes containing insults, inproper language or that is " +
    "revealing secrets that should be kept may be removed by the " +
    "village council at any rate.\n");
    set_board_name(HOBBIT_BOARD_DIR);
    set_num_notes(50);
    set_silent(1);
    set_show_lvl(0);
    set_remove_rank(WIZ_LORD);
    set_remove_str("Only the village council may remove arbitrary notes.\n");
}
/* EOF */
