inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/wild/pass/guild/defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/money.h"

#define TO this_object()
#define TP this_player()

#define NUM             sizeof(query_money_types(-1))


object meditate;

create_room() {
	set_short("Training Room");
	set_long("You have entered the training room for the newer "
		+"members of the Drow Academy. They teach some skills "
		+"but not to a high level. Here you will learn the "
		+"word of Lloth, the Spider Queen, and grow to love "
		+"her. There is a weapon rack against the far wall, "
		+"and the whole room is lined with an eerie fire. "
		+"There is a small sign posted on the wall near the "
		+"rack. To the east is the entrance chamber of the "
		+"Academy. That is the only way out of this small "
		+"chamber.\n");
add_item(({"rack","weapon rack"}),"This is a truly glorious rack! It "
		+"displays numerous weapons, mainly swords and "
		+"similiar bladed weapons.\n");
add_item(({"weapon","weapons"}),"The weapons are all exquisitely "
		+"decorated and crafted from a strange metal that "
		+"seems to radiate magic and enchantment.\n");
add_item(({"chamber"}),"It is to the east.\n");
add_item(({"sign","small sign"}),"Amazingly enough it "
	+"has words on it!\n");
add_cmd_item("sign","read","This is the training room "
	+"for the Drow Academy. Here you may <improve> or <learn> "
	+"skills, or <meditate> to check your stat preferences.\n");
add_exit(DGUILD + "common/joinroom", "east", 0);
add_prop(ROOM_NO_TIME_DESC,1);
add_prop(ROOM_I_INSIDE,1);
create_guild_support();
create_skill_raise();
set_up_skills();
}

 
init() {
    init_guild_support();
    init_skill_raise();
    ::init();
}



set_up_skills() {


    sk_add_train(SS_PARRY,      train_text(SS_PARRY),      0,0,50 );
    sk_add_train(SS_DEFENCE,    train_text(SS_DEFENCE),    0,0,50 );
    sk_add_train(SS_2H_COMBAT,  train_text(SS_2H_COMBAT),  0,0,50 );
    sk_add_train(SS_SPELLCRAFT, train_text(SS_SPELLCRAFT), 0,0,50 );
    sk_add_train(SS_AWARENESS,  train_text(SS_AWARENESS),  0,0,50 );
    sk_add_train(SS_TRACKING,   train_text(SS_TRACKING),   0,0,50 );
    sk_add_train(SS_APPR_OBJ,   train_text(SS_APPR_OBJ),   0,0,50 );
    sk_add_train(SS_WEP_SWORD,  train_text(SS_WEP_SWORD),  0,0,50 );
    sk_add_train(SS_APPR_VAL,   train_text(SS_APPR_VAL),   0,0,50 );
    sk_add_train(SS_FORM_CONJURATION, train_text(SS_FORM_CONJURATION),  0,0,50 );

}

train_text(skill) {
    string what;

    switch(skill) {

        case SS_SPELLCRAFT:
            what="cast spells";
            break;
        case SS_PARRY:
            what="use a weapon to block attacks";
            break;
        case SS_DEFENCE:
            what="defend without weapons";
            break;
        case SS_WEP_SWORD:
            what="use a sword";
            break;
	case SS_AWARENESS:
	    what="notice things";
	    break;
	case SS_TRACKING:
	    what="follow tracks";
	    break;
	case SS_APPR_OBJ:
	    what="estimate the size and weight of objects";
	    break;
	case SS_APPR_VAL:
	    what="estimate the value of something";
	    break;
	case SS_FORM_CONJURATION:
	    what="create magical things and affects";
	    break;
	case SS_2H_COMBAT:
	    what="fight with both hands";
	    break;
    }
    return what;
}
