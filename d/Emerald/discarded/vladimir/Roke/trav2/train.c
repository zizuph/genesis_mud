
/*     The Modified Guild for the travellers..   */

/*         If the guild is closed you can toggle this by doing,
 *         > Call here close_guild
 *         This is a quick way to close/open it if needed
 */

inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/std/room";

#include "/d/Roke/varl/atuan/cape/guild/default.h"
#include "/d/Roke/common/defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/money.h"


#define NUM             sizeof(query_money_types(-1))

#define CLOSED          0       /* 1 = closed,   0 = open.  */

int closed;
object meditate;


create_room() {
    object board, box;

    closed = CLOSED;

    set_short("Travellers Training Room");
    set_long(BS("You are in the training room of the Traveller's guild."
	+ " It is a large cosy room lit by a single flickering lantern which"
	+ " hangs from the ceiling high above. A number of maps cover"
	+ " the walls which detail some of the areas that guild memebers"
	+ " have explored. It is possible to improve your skills here,"
	+ " or meditate and set your preferences.",70));


    add_item("fire","The fire brings heat to the house.\n");

    add_item(({"paintings","pictures"}),"You see the pictures of three mighty"+
             " wizards. You see that\nthey are the wizards whose statues are "+
             "located at the town square.\n");
    add_item(({"lantern","flickering lantern"}),"It hangs from an iron"
	+ " hook on the ceiling, and provides a steady illumination.\n");
    add_item(({"map","maps"}),"The are finely drawn and perfectly coloured"
	+ " showing major roads and landmarks.\n");


    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop("_room_has_fire",1);

    add_exit(CAPE + "guild/balcony", "east", 0);
 

    create_guild_support();
    create_skill_raise();
    set_up_skills();
}

wizinfo() {
   return ("If there should be due cause to close down the guild, do so by\n"+
           "typing:  Call here close_guild\n"+
           "This will temporarily prevent mortals from entering. After a\n"+
           "reboot, the guild will be open by default. Please send me some\n"+
           "mail if there is anything that needs to be fixed.\n\n   /Ged.\n");
}

enter_inv(ob, from) {
    ::enter_inv(ob, from);

    if (!query_ip_number(ob) || !closed)
        return;

    if (ob->query_wiz_level())
        write("\n\nWARNING!\nYou shouldn't be here. "+
              "I'm doing some work on the guild.\n");
    else {
        write("The guild is closed. Come back later.\n");
        ob->move("/d/Roke/varl/atuan/cape/cove4");
    }
}


init() {
    init_guild_support();
    init_skill_raise();
    ::init();
}
close_guild() {
    if (closed) {
        closed = 0;
        return "  **The guild is now open**";
    }
    closed = 1;
    return "  **The guild is now closed**";
}

query_closed() { return closed; }

set_up_skills() {

    /* Add skill that can be trained. Do not add all skills, and vary a bit */

    sk_add_train(SS_APPR_MON,   train_text(SS_APPR_MON),      0,0,35 );
    sk_add_train(SS_APPR_OBJ,   train_text(SS_APPR_OBJ),      0,0,35 );
    sk_add_train(SS_LANGUAGE,   train_text(SS_LANGUAGE),      0,0,40 );
    sk_add_train(SS_TRACKING,   train_text(SS_TRACKING),      0,0,40 );
    sk_add_train(SS_WEP_POLEARM,     train_text(SS_WEP_POLEARM),   0,0,50 );
    sk_add_train(SS_CLIMB,      train_text(SS_CLIMB),         0,0,45 );
    sk_add_train(SS_ANI_HANDL,  train_text(SS_ANI_HANDL),     0,0,30 );
    sk_add_train(SS_LOC_SENSE,  train_text(SS_LOC_SENSE),     0,0,50 );
    sk_add_train(SS_SWIM,       train_text(SS_SWIM),          0,0,50 );
    sk_add_train(SS_TRADING,    train_text(SS_TRADING),       0,0,50 );

}

train_text(skill) {
    string what;

    switch(skill) {       
        case SS_APPR_MON:
            what="appraise your opponents";
            break;
        case SS_APPR_OBJ:
            what="appraise different objects";
            break;
        case SS_LANGUAGE:
            what="understand foreign languages";
            break;
        case SS_TRACKING:
            what="tracking";
            break;
    case SS_WEP_POLEARM:
        what="handle a polearm";
        break;
        case SS_CLIMB:
            what="climb walls and mountains";
            break;
        case SS_ANI_HANDL:
            what="animal handling";
            break;
        case SS_AWARENESS:
            what="be aware of your surroundings";
            break;
        case SS_LOC_SENSE:
            what="sense of location";
            break;
        case SS_SWIM:
            what="swim";
            break;
        case SS_TRADING:
            what="trade sucessfully";
            break;
        default:
            what="do nothing. THIS IS A BUG";
            break;
    }
    return what;
}
