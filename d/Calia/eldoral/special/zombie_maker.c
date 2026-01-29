#pragma strict_types

#include "defs.h"

inherit "/std/object";

string *names,
       *adjs,
       race;
int gender,
    *stats,
    *prefs,
    scars,
    height,
    weight,
    volume;
mapping skillmap,
        remembered;

public void
convert_to_zombie()
{
    int i,
        temp; 
    object zombie;
    setuid();
    seteuid(getuid());

    zombie = clone_object(NPC + "zombie");
    zombie->set_name(names);
    zombie->set_adj(adjs);
    zombie->set_race_name(race + " zombie");
    zombie->set_gender(gender);
    zombie->set_stats(stats);
    zombie->set_scar(scars);
    zombie->add_prop(CONT_I_HEIGHT, height);
    zombie->add_prop(CONT_I_WEIGHT, weight);
    zombie->add_prop(CONT_I_VOLUME, volume);
    for (i = 0; i < sizeof(m_indexes(skillmap)); i++)
    {
        temp = m_indexes(skillmap)[i];
        zombie->set_skill(temp, skillmap[temp]);
    }
     
    zombie->stats_to_acc_exp();
    zombie->set_hp(10000);
    zombie->set_mana(10000);
    zombie->set_learn_pref(prefs);
    zombie->set_zombie_remembered(remembered);
    zombie->save_my_zombie();
    zombie->remove_object();

}

public void
make_me_zombie(string who)
{
    object player;
    int i;
    string *skillarr,
           temp;
    
    player = find_player(who);

    if (!player)
        return;

    log_file("eldoral_zombies", capitalize(who) + " was turned " +
        "into a zombie with statave " +
        player->query_average_stat() + " on " + ctime(time()) + ".\n");

    names = player->query_names();
    names += ({"zombie"});
    names -= ({OB_NAME(player)});
    adjs = player->query_adjs();
    race = player->query_race();
    gender = player->query_gender();
    stats = ({});
    for (i = 0; i < 9; i++)
        stats += ({player->query_stat(i)});
    skillarr = player->query_all_skill_types();
    skillmap = ([]);
    for (i = 0; i < sizeof(skillarr); i++)
    {
        temp = skillarr[i];
        skillmap[temp] = player->query_skill(temp);
    }
    scars = player->query_scar();
    height = player->query_prop(CONT_I_HEIGHT);
    weight = player->query_prop(CONT_I_WEIGHT);
    volume = player->query_prop(CONT_I_VOLUME);
    prefs = player->query_learn_pref(-1);
    remembered = player->query_remembered();
    convert_to_zombie();
}

public varargs void
wake_up_zombies(object ob = this_player())
{
    object where;
    object zombie;
    string *names;
    int i;

    if (interactive(ob))
        where = environment(ob);
    else
        where = ob;

    seteuid(getuid());

    names = get_dir("/d/Calia/eldoral/special/zombies/*.o");
    for (i = 0; i < sizeof(names); i++)
    {
        zombie = clone_object("/d/Calia/eldoral/npc/zombie");
        zombie->create_zombie(names[i][0..strlen(names[i])-3]);
        zombie->move(where);
    }
}

public void
animate_corpse(object ob, string name)
{
    object zombie;

    zombie = clone_object(NPC + "zombie");
    zombie->create_zombie(capitalize(name));
    tell_room(environment(ob), "Suddenly, the corpse begins " +
        "to stir, and stands up again!\n");
    zombie->move(environment(ob));
    all_inventory(ob)->move(zombie, 1);
    ob->remove_object();
    zombie->command("wear all");
    zombie->command("wield all");
    zombie->command("groan");
}
