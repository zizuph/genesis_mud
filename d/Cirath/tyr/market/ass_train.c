inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/tyr/tyr.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
 
 
object meditate;
 
#include "/d/Cirath/common/mobber.h"


void
reset_room()
{
    object npc = present ("lim", TO);
    if(!objectp(npc))
    {
        bring_room_mob("lim", TYR_NPC+"ass", 1, 1);
    }
}

create_room() {
        set_short("Bard's Study Chambers");
        set_long("You have entered a small dank room behind the Bard's Hand "
	+"bar.  As you look around, you see a few people honing their skills "
	+"at hiding and other thief like skills.  The floor is covered in "
	+"layers of some course material which seems to be doubling as padding. "
	+"A small sign is posted on the wall which appears to be readable.\n");
add_item(({"picture","pictures"}),"They look like pictures of various "
                +"creatures with large Xs where they should be attacked.\n");
add_item(({"walls","wall"}),"They are amazingly bare. You see a dummy "
	+"designed to help with your pick pocketing skills, as well as "
	+"a large series of pictures depicting bodies of various creatures "
	+"and the best place to strike them.\n");
add_item(({"sign","small sign"}),"Amazingly enough it "
        +"has words on it!\n");
add_cmd_item("sign","read","You may <learn> or <improve> certain skills "
        +"that pertain to the Bardic arts here.  Use your skills carefully, "
        +"and do not allow yourself to be caught in the act.\n");
add_item("floor","It is hard to see because the mats cover it.\n");
add_item(({"mat","mats"}),"They are rough mats that protect one from injury "+
	"during training.\n");
add_prop(ROOM_I_INSIDE,1);
   add_exit(TYR_MARKET+"housfngr","south");
create_guild_support();
create_skill_raise();
set_up_skills();
   set_alarm(1.0,0.0,"reset_room");
}
 
 
init() {
    init_guild_support();
    init_skill_raise();
    ::init();
}
 
 
 
set_up_skills() {
 
 
    sk_add_train(SS_WEP_KNIFE,    train_text(SS_WEP_KNIFE),  0,0,30 );
    sk_add_train(SS_DEFENCE,      train_text(SS_DEFENCE),    0,0,20 );
    sk_add_train(SS_HIDE,         train_text(SS_HIDE),       0,0,20 );
    sk_add_train(SS_SNEAK,        train_text(SS_SNEAK),      0,0,20 );
    sk_add_train(SS_AWARENESS,    train_text(SS_AWARENESS),  0,0,30 );
    sk_add_train(SS_PICK_POCKET,  train_text(SS_PICK_POCKET),0,0,20 );
    sk_add_train(SS_CLIMB,        train_text(SS_CLIMB),      0,0,30);
    sk_add_train(SS_ACROBAT,      train_text(SS_ACROBAT),    0,0,20 );
    sk_add_train(SS_HERBALISM,    train_text(SS_HERBALISM),  0,0,20 );
 
}
 
train_text(skill) {
    string what;
    switch(skill) {
 
        case SS_HIDE:
            what="hide your self";
            break;
        case SS_SNEAK:
            what="move silently from room to room";
            break;
        case SS_DEFENCE:
            what="defend without weapons";
            break;
        case SS_ACROBAT:
            what="do acrobatic moves";
            break;
        case SS_AWARENESS:
            what="notice things";
            break;
        case SS_CLIMB:
            what="climb surfaces";
            break;
        case SS_WEP_KNIFE:
            what="use a knife";
            break;
        case SS_PICK_POCKET:
            what="steal things from people";
            break;
        case SS_HERBALISM:
            what="identify herbs";
            break;
    }
    return what;
}


