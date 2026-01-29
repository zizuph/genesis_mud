/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/d/Terel/std/monster";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TO  this_object()
#define TP  this_player()
#define ETO environment(TO)

#define DEFAULT_SPELL_DELAY 10

public void set_mystic_skills(int p);
public void set_piety(int piety);
public void set_spell_prop(object ob);
public void set_spell_delay(int delay);
public void add_mystic_spell(string name);
public string *query_mystic_spells();

static int auto_hail = 0, auto_salute = 0, auto_reverence = 0;

int spell_delay = DEFAULT_SPELL_DELAY;
string *spells = ({});

public void
set_rank(int rank)
{
    set_guild_stat(SS_OCCUP,  stat_to_exp((200*(rank+1))/(MYSTIC_PATRIARCH+2)));
    set_guild_stat(SS_LAYMAN, stat_to_exp((130*(rank+1))/(MYSTIC_PATRIARCH+2)));
    set_mystic_skills((100*(rank+1))/(MYSTIC_PATRIARCH+1));
    set_piety((1000*(rank+1))/(MYSTIC_PATRIARCH+1));
    set_skill(MYSTIC_RANK, rank);
}

public void
set_piety(int piety)
{
    set_skill(PIETY, piety);
}

public void
set_blessed(int blessed)
{
    add_prop(MYSTIC_BLESSED, blessed);
}

public void
set_mystic_skills(int p)
{
    set_skill(SS_DEFENCE,            (MYSTIC_MAX_DEFENCE*p)/100);
    set_skill(SS_AWARENESS,          (MYSTIC_MAX_AWARENESS*p)/100);
    set_skill(SS_PARRY,              (MYSTIC_MAX_PARRY*p)/100);
    set_skill(SS_CLIMB,              (MYSTIC_MAX_CLIMB*p)/100);
    set_skill(SS_WEP_SWORD,          (MYSTIC_MAX_SWORD*p)/100);
    set_skill(SS_WEP_KNIFE,          (MYSTIC_MAX_KNIFE*p)/100);
    set_skill(SS_APPR_MON,           (MYSTIC_MAX_APPR_MON*p)/100);
    set_skill(SS_APPR_OBJ,           (MYSTIC_MAX_APPR_OBJ*p)/100);
    set_skill(SS_LOC_SENSE,          (MYSTIC_MAX_LOC_SENSE*p)/100);
    set_skill(SS_SPELLCRAFT,         (MYSTIC_MAX_SPELLCRAFT*p)/100);
    set_skill(SS_LANGUAGE,           (MYSTIC_MAX_LANGUAGE*p)/100);
    set_skill(SS_FORM_ABJURATION,    (MYSTIC_MAX_ABJURATION*p)/100);
    set_skill(SS_FORM_CONJURATION,   (MYSTIC_MAX_CONJURATION*p)/100);
    set_skill(SS_FORM_DIVINATION,    (MYSTIC_MAX_DIVINATION*p)/100);
    set_skill(SS_FORM_TRANSMUTATION, (MYSTIC_MAX_TRANSMUTATION*p)/100);
    set_skill(SS_FORM_ENCHANTMENT,   (MYSTIC_MAX_ENCHANTMENT*p)/100);
    set_skill(SS_ELEMENT_AIR,        (MYSTIC_MAX_AIR*p)/100);
    set_skill(SS_ELEMENT_DEATH,      (MYSTIC_MAX_DEATH*p)/100);
    set_skill(SS_ELEMENT_FIRE,       (MYSTIC_MAX_FIRE*p)/100);
    set_skill(SS_ELEMENT_EARTH,      (MYSTIC_MAX_EARTH*p)/100);
    set_skill(SS_CHANNELING,         (MYSTIC_MAX_CHANNELING*p)/100);
}

public void
make_me_mystic()
{
    object shadow, ring;

    seteuid(getuid());

    shadow = clone_object(MYSTIC_SHADOW);
    if (shadow->shadow_me(TO, GUILD_TYPE, GUILD_STYLE, GUILD) != 1)
        shadow->remove_shadow();

    shadow = clone_object(MYSTIC_LAY_SHA);
    if (shadow->shadow_me(TO, LAY_TYPE, LAY_STYLE, LAY_NAME) != 1)
        shadow->remove_shadow();

    if (query_ghost()) return;
    
/*
    ring = clone_object(GUILD_DIR + "mring");
    ring->add_prop("_mystic_s_owner", TO->query_real_name());
    ring->move(TO);
*/
}

public void
enable_auto_hail()
{
    auto_hail = 1;
}

public void
disable_auto_hail()
{
    auto_hail = 0;
}

public void
enable_auto_salute()
{
    auto_salute = 1;
}

public void
disable_auto_salute()
{
    auto_salute = 0;
}

public void
enable_auto_reverence()
{
    auto_reverence = 1;
}

public void
disable_auto_reverence()
{
    auto_reverence = 0;
}

public string
query_auto_prop(string cmd)
{
    if (cmd == "hail")
        return ("_hailed_by_" + query_name());
    if (cmd == "salute")
        return ("_saluted_by_" + query_name());
    if (cmd == "reverence")
        return ("_reverenced_by_" + query_name());
    return "";
}

public void
do_cmd(string cmd, object ob)
{
    if (!ob || environment(ob) != ETO || !MEMBER(ob)) return;

    if (cmd == "reverence" && !T_WIZ(ob) &&
        TO->query_mystic_rank() >= ob->query_mystic_rank()) return;

    command(cmd + " " + ob->query_real_name());
    ob->add_prop(query_auto_prop(cmd), 1);
}

public void
init_living()
{
    ::init_living();

    if (!CAN_SEE(TO, TP)) return;

    if (TP->query_prop(query_auto_prop("hail")) == 0 && auto_hail)
        set_alarm(4.0, -1.0, &do_cmd("hail", TP));

    if (TP->query_prop(query_auto_prop("salute")) == 0 && auto_salute)
        set_alarm(5.0, -1.0, &do_cmd("salute", TP));

    if (TP->query_prop(query_auto_prop("reverence")) == 0 && auto_reverence)
        set_alarm(6.0, -1.0, &do_cmd("reverence", TP));
}

public void
set_spell_delay(int delay)
{
    if (delay > 0)
        spell_delay = delay;
}

public int
query_spell_delay()
{
    return spell_delay;
}

public void
add_mystic_spell(string name)
{
    if (!name) return;

    if (sizeof(spells) == 0)
        spells = ({ name });
    else
        spells += ({ name });
}

public string *
query_mystic_spells()
{
    return spells;
}

public void
spell_attack(object me, object victim)
{
    string spell;

    if (sizeof(spells)) {
        spell = spells[random(sizeof(spells))];
        command(check_call(spell));
    }

    set_alarm(itof(10+random(spell_delay)), -1.0, &set_spell_prop(TO));
}

public void
create_monster()
{
    ::create_monster();

    set_rank(MYSTIC_NOVITIATE);
    set_blessed(1);
    add_prop("purified", 1);
    set_tell_active(1);
    set_spell_prop(TO);

    set_alarm(1.0, -1.0, make_me_mystic);
}

public void
set_spell_prop(object ob)
{
    add_prop(LIVE_O_SPELL_ATTACK, ob);
}

public void
notify_spell_enemy_gone(object enemy)
{
    set_alarm(itof(2+random(spell_delay)), -1.0, &set_spell_prop(TO));
}

public int
query_see_special_msg()
{
    return 1;
}
