inherit "/std/weapon";

#include "/d/Terel/common/terel_std_rec.h"
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>

#define TP            this_player()
#define TO            this_object()
#define ETO           environment(TO)
#define ETP           environment(TP)
#define LDIRS         ({"Terel", "common", "town", "mansion",\
                        "tapestry_room", "battlefield_1", "battlefield_2"})

int tried_to_drop_flag = 0;

public int
query_value()
{
    return 0;
}

public int
try_hit(object ob)
{
    if (query_wielded()->query_attack()->id("thane_dark_one"))
        return 1;

    query_wielded()->catch_msg(
              "You prepare to strike with the ancient sword, when, like a " +
              "faint echo, you hear a voice in the back of your mind: 'Mine " +
              "is not to be wielded against this unworthy opponent. Till " +
              "the fabric of time itself is torn, only the " +
              "Darkest is to be cleaved by my blade...'  The echo dies and " +
              "your hand drops from the hilt of the sword.\n");
    query_wielded()->command("$unwield thane_quest_sword");
    return -1;
}

public void
create_weapon()
{
    set_name("sword");
    add_name("thane_quest_sword");
    add_name("LightBringer");
    add_name("lightbringer");
    set_short("ancient sword");
    set_adj("ancient");
    set_long("@@glow_func");
    set_hit(100);           /* only to be used against the Dark One */
    set_pen(100);           /* (see above)                          */

    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);
    add_prop("_wep_i_blademaster_no_exchange",1);

    add_prop(OBJ_I_WEIGHT, 1600);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop("mystic_weapon", 1);  /* allow mystics to use this sword */
    add_prop(OBJ_M_NO_SELL, "A voice sounds in your mind, as if from " +
                            "a great distance: Mine is not to be bought " +
                            "or sold; profit is no part of my Purpose.\n");
    add_prop(OBJ_M_NO_GIVE, "As if from a great distance, you hear the " +
                            "ancient sword itself speak to you: 'When you " +
                            "took me in hand, you obliged yourself to a great " +
                            "Purpose; none can take your place. Drop me, if " +
                            "you feel you must, and I shall release you " +
                            "from my ageless quest.'\n");
    add_prop(OBJ_M_NO_DROP, "@@catch_drop");
}

public void
do_consume()
{
    if (ETO && ETO->query_prop(ROOM_I_IS)) {
        tell_room(ETO, "The " + short() + " is rapidly consumed.\n");
    } else if (ETO && living(ETO)) {
        ETO->catch_msg("The " + short() + " is rapidly consumed.\n");
        ETO->catch_msg("You are burned.\n");
        ETO->reduce_hit_point(30);
        ETO->do_die(TO);
    }
    remove_object();
}

public void
do_flame()
{
    if (ETO && ETO->query_prop(ROOM_I_IS)) {
        tell_room(ETO, "The " + short() + " bursts into flames.\n");
    } else if (ETO && living(ETO)) {
        ETO->catch_msg("The " + short() + " bursts into flames.\n");
        tell_room(environment(ETO), "The " + short() + " " +
                  QTNAME(ETO) + " has, bursts into flames.\n", ETO);
        ETO->catch_msg("You are burned.\n");
        ETO->reduce_hit_point(30);
        ETO->do_die(TO);
    }
    set_alarm(6.0, -1.0, do_consume);
}

public void
leave_msg(object who)
{
    if (who)
        who->catch_msg("As the " + short() + " leaves you, " +
                       "you hear within your mind a faint echo: 'Perhaps " +
                       "you are not " + TP->query_pronoun() + " whom " +
                       "I have so long sought, then. Fare thee well, " +
                       "traveler!'\n");
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    
    if (from && living(from)) {
        set_short("ancient sword");
        set_alarm(1.0, -1.0, &leave_msg(from));
        set_alarm(5.0, -1.0, do_flame);
    }
}

public string
glow_func()
{
    string      *player_loc, *temp;
    string      str;
    int i, light_val;

    light_val = 0;
    player_loc = explode(file_name(ETP), "/");
    for (i=0; i<sizeof(player_loc); i++)
        if (member_array(player_loc[i], LDIRS) >= 0)
            light_val++;
    switch (light_val)
    {
        case 0: str= "glows very, very faintly"; break;
        case 1: str= "glows faintly"; break;
        case 2: str= "glows brightly"; break;
        case 3: str= "shines with an inner light"; break;
        case 4: str= "shines with a dazzling glare"; break;
        case 5: str= "burns with a holy brilliance"; break;
        case 6: str= "burns with the power of its makers"; break;
    }
    return "This mighty sword might have been forged in the fires of " +
           "the sun itself. The blade, beautifully formed of a metal " +
           "unknown to you, is inlaid with runes of mithril, and in " +
           "the hilt a pure white stone " + str + ". The sword is " +
           "ancient; though the untarnished blade sparkles as though " +
           "it were tempered yesterday, you feel its great age " +
           "resonating somewhere deep within your very soul.\n";
}

public int
do_read(string str)
{
    if (str != "runes" && str != "runes on sword") return 0;

    /* Check language skill. High enough, should read ancient elven runes
     * about origin and purpose of sword. Lower,  should identify runes
     * as Elven. Lower,  no clue.
     */
    if (TP->query_skill(SS_LANGUAGE) > 40)
    {
        set_short("ancient sword named LightBringer");
        write("You recognize the runes as ancient Elvish. Studying them "
        + "carefully, you make out an inscription:\n"
        + "     We, who have forseen your need, do forge this blade in the\n"
        + "     heat of truth and the fire of justice. Hither do we christen\n"
        + "     it LightBringer. May it serve you well in the time of darkness,\n"
        + "     and strike down the One who is most Dark. Wield it with \n"
        + "     discrimination, for only in the presence of the Dark One shall\n"
        + "     LightBringer fulfill its noble purpose.\n");
    }
    else if (TP->query_skill(SS_LANGUAGE) > 15)
    {
        set_short("ancient sword, engraved with Elvish runes");
        write("You recognize the runes as ancient Elvish, but your " +
              "study of languages has not progressed far enough to " +
              "let you read them.\n");
    }
    else
    {
        write("The runes are beautiful and complex, but you have no " +
              "idea what they say or even what language they might " +
              "be in.\n");
    }
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_read, "read");
}

public int
catch_drop()
{
    if (tried_to_drop_flag)
    {
         return 0;
    }
    else
    {
         tried_to_drop_flag = 1;
         if (ETO && living(ETO))
             ETO->catch_msg("A thought sounds in the back of your " +
                            "mind, almost as if it were your own: " +
                            "'Drop me and I shall return to the " +
                            "place from whence I came. You have " +
                            "been warned.'\n");
         return 1;
    }
}
