/*         If the guild is closed you can toggle this by doing,
 *         > Call here close_guild
 *         This is a quick way to close/open it if needed
 */

inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";
inherit "/std/room";


#include "/d/Roke/common/defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/money.h"
#include "/d/Roke/Cirath/barbarians/skills.h"

#define NUM             sizeof(query_money_types(-1))

#define CLOSED          0       /* 1 = closed,   0 = open.  */

int closed;
object meditate;


create_room() { 
    object board, box;

    closed = CLOSED; 

    set_short("Training tent");
    set_long(break_string(
             "This is the tent where the barbarians improve their "+
             "skills in combat. Many barbarians are training here.\n",60));

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
 
    add_exit(STDIR + "common/gont/re/a5", "north", 0);
    add_exit(REDIR + "common","common");
    clone_object(REDIR+"obj/charity")->move(TO);

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
        ob->move("/d/Roke/common/gont/re/a5");
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

    sk_add_train(SLAYING,         train_text(SLAYING),         "slaying",200,70 );
    sk_add_train(BONKING,         train_text(BONKING),         "bonking",200,70 );
    sk_add_train(CHOPPING,        train_text(CHOPPING),        "chop enemy",150,70 );
    sk_add_train(HOLDING,         train_text(HOLDING),         "hold enemy",150,70 );
    sk_add_train(STABBING,        train_text(STABBING),        "stab enemy",150,70 );
    sk_add_train(BLOCKING,        train_text(BLOCKING),        "block enemy",150,70 );
    sk_add_train(SS_APPR_MON,     train_text(SS_APPR_MON),     0,0,60 );
    sk_add_train(SS_WEP_SWORD,    train_text(SS_WEP_SWORD),    0,0,70 );
    sk_add_train(SS_WEP_AXE,      train_text(SS_WEP_AXE),      0,0,70 );
    sk_add_train(SS_PARRY,        train_text(SS_PARRY),        0,0,70 );
    sk_add_train(SS_DEFENCE,      train_text(SS_DEFENCE),      0,0,70 );
    sk_add_train(SS_BLIND_COMBAT, train_text(SS_BLIND_COMBAT), 0,0,50 );
    sk_add_train(SS_UNARM_COMBAT, train_text(SS_UNARM_COMBAT), 0,0,20 );

}

train_text(skill) {
    string what;

    switch(skill) {
        case SLAYING:
            what="slay your enemy";
            break;

        case BONKING:
            what="bonk your enemies with your fist/weapon";
            break;
        case CHOPPING:
            what="chop your enemy";
            break;
        case HOLDING:
            what="stop your enemy from running away";
            break;
        case STABBING:
            what="stab your enemy";
            break;
        case BLOCKING:
            what="block your enemies from hitting you";
            break;
        case SS_APPR_MON:
            what="appraise your enemies";
            break;
        case SS_WEP_SWORD:
            what="fighting with swords";
            break;
        case SS_WEP_AXE:
            what="fighting with axes";
            break;
        case SS_PARRY:
            what="parry your enemy's attempts to hit you";
            break;
        case SS_DEFENCE:
            what="defend yourself";
            break;
        case SS_BLIND_COMBAT:
            what="fight in darkness";
            break;
        case SS_UNARM_COMBAT:
            what="fight without weapons";
            break;
        default:
            what="do nothing. THIS IS A BUG";
            break;
    }
    return what;
}
