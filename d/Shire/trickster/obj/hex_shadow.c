#pragma save_binary

inherit "/std/shadow";

#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#define QSW query_shadow_who()
#define HIS_HER(x) x->query_possessive()
#define HEX1 ({ "", \
        " is picking ", \
        " has a sign on ", \
        " has an upside-down nose on ", \
        " is missing ", \
        " is walking on ", \
        " has yellowish-green polka-dots in ", \
        " has toilet paper stuck to ", \
        " is on ", \
        " has a HUGE wart on the end of " \
})
#define HEX2 ({ "", \
        " nose", \
        " back saying, \"KICK ME!!\"\n", \
        " chin", \
        " right eyebrow", \
        " elbows", \
        " purple hair", \
        " shoe", \
        " knees worshipping Nob Nar", \
         " extremely looonnnggg nose" \
})

varargs public mixed
short(object who) 
{
    string first_half, second_half, desc, hex;
    int hex_num;

    if (!who)
	who = this_player();

    hex_num = random(sizeof(HEX1));
    if (!hex_num)
    {
        if (QSW->query_race() == "goblin")
            hex = " looks more like an elf than a goblin!\n";
        else
            hex = " looks more like a goblin than " + 
                  LANG_ADDART(QSW->query_race()) + "!\n";
    }
    else
        hex = HEX1[hex_num] + HIS_HER(QSW) + HEX2[hex_num];

    /*
     * If a specific short is set with set_short, use that description
     */
    if (strlen(QSW->query_short()))
    {
        desc = QSW->short(who);
        return desc + hex;
    }


    if (QSW->notmet_me(who))
	desc = QSW->query_nonmet_name();
    else
	desc = QSW->query_met_name();

    desc += hex;

    if (QSW->query_prop(LIVE_S_EXTRA_SHORT))
	desc += " and" + QSW->query_prop(LIVE_S_EXTRA_SHORT);

    return desc;
}

int query_hex_shadow()
{
  return 666;
}

void destruct_hex_shadow(int delay)
{
  set_alarm(itof(delay),0.0,remove_shadow);
}
