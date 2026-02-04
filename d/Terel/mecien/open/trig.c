inherit "/std/monster";

create_monster()
{
    int i;

    set_name("goblin");
    set_living_name("goblin");
    set_long("It's very small but it looks back on you and shows its teeth.\n");
    set_race_name("goblin");
    set_adj("small");

    set_gender(2); /* male = 0, female = 1, other = 2 */

    default_config_mobile(7);

    set_alignment(-70);

    trig_new("%s 'bows' %s", "bowing");
}

bowing(str1, str2)
{
    command("say I see " + str1 + " bowing " + extract(str2, 0, strlen(str2) - 2));
    command("smile " + lower_case(str1));
}



