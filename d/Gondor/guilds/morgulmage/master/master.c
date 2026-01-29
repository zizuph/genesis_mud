/*
 *  /d/Gondor/guilds/morgulmage/master/master.c
 *
 *  This room contains all the control functions for the Society of Morgul
 *  Mages. Obviously it's a very bad idea to touch something here if you
 *  do not know what you are doing.
 *
 *  Created by Eowul, March 2009
 */
#pragma strict_types
#pragma no_clone

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"

#include <ss_types.h>
#include <macros.h>
#include <language.h>

inherit "/std/object";
inherit "/lib/time";

private void load_data();
private void save_data();
public int query_is_nazgul(mixed mage);
public void remove_player_as_nazgul(mixed nazgul, string reason = 0);

#include "member.c"
#include "friendorfoe.c"
#include "messages.c"
#include "position.c"
#include "activity.c"
#include "nazgul.c"
#include "joinleave.c"
#include "spells.c"
#include "options.c"
#include "winged_steed.c"

public void create_object()
{
    set_name("MorgulMage Master Object");
    load_data();
}

private void load_data()
{
    setuid();
    seteuid(getuid());
    if(file_size(MORGUL_MASTER_SAVE + ".o") > 0) {
        restore_object(MORGUL_MASTER_SAVE);
    }
    
    purge_nonexisting();
    purge_nonexisting_friend_or_foe();
    validate_nazgul();
    validate_reign_of_lord_nazgul();
    validate_votes("nazgul_vote");
    validate_votes("nazgul_lord_vote");
    purge_positions();
    startup_activity_meter();
}

private void save_data()
{
    setuid();
    seteuid(getuid());
    save_object(MORGUL_MASTER_SAVE);
}

void armageddon_shutdown()
{  
    save_data();
}