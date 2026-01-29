inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/d/Kalad/room_std";

#include "/d/Kalad/common/zhent/defs.h"
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
		+"members of the Black Network. Here skills may be "
		+"learned to aid the cause of the Zhentarim. The room "
		+"contains a small cabinet, as well as a mat to "
		+"practice on. Otherwise, it is rather bare.\n");
add_item(({"cabinet"}),"It is used to store knives in.\n");
add_item(({"knives"}),"They are used to practice with.\n");
add_item(({"mat"}),"It is used to soften hard tumbles, and to practice "
	+"acrobatics on.\n");
add_item(({"sign","small sign"}),"Amazingly enough it "
	+"has words on it!\n");
add_cmd_item("sign","read","This is the training room "
	+"for the Zhentarim. Here you may <improve> or <learn> "
	+"skills, or <meditate> to check your stat preferences.\n");
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

    /* Add skill that can be trained. Do not add all skills, and vary a bit */

    sk_add_train(SS_PARRY,      train_text(SS_PARRY),      0,0,20 );
    sk_add_train(SS_DEFENCE,    train_text(SS_DEFENCE),    0,0,35 );
    sk_add_train(SS_SNEAK,      train_text(SS_SNEAK),      0,0,90 );
    sk_add_train(SS_HIDE,       train_text(SS_HIDE),       0,0,90 );
    sk_add_train(SS_AWARENESS,  train_text(SS_AWARENESS),  0,0,75 );
    sk_add_train(SS_APPR_VAL,   train_text(SS_APPR_VAL),   0,0,75 );
    sk_add_train(SS_APPR_OBJ,   train_text(SS_APPR_OBJ),   0,0,75 );
    sk_add_train(SS_WEP_KNIFE,  train_text(SS_WEP_KNIFE),  0,0,50 );
    sk_add_train(SS_OPEN_LOCK,  train_text(SS_OPEN_LOCK),  0,0,90 );
    sk_add_train(SS_ACROBAT,    train_text(SS_ACROBAT),    0,0,75 );

}

train_text(skill) {
    string what;

    switch(skill) {

        case SS_OPEN_LOCK:
            what="open locks";
            break;
        case SS_PARRY:
            what="use a weapon to block attacks";
            break;
        case SS_DEFENCE:
            what="defend without weapons";
            break;
        case SS_WEP_KNIFE:
            what="use a knife";
            break;
	case SS_AWARENESS:
	    what="notice things";
	    break;
	case SS_SNEAK:
	    what="move around while hidden";
	    break;
	case SS_APPR_OBJ:
	    what="estimate the size and weight of objects";
	    break;
	case SS_APPR_VAL:
	    what="estimate the value of something";
	    break;
	case SS_HIDE:
	    what="remain hidden from view";
	    break;
	case SS_ACROBAT:
	    what="tumble effectively";
	    break;
    }
    return what;
}
