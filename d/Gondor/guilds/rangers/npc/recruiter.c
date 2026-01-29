inherit "/std/monster";

public void
create_monster()
{
    set_name("recruiter");
    set_race_name("human");
    set_adj("temporary");
    add_adj("recruiter");
    set_long("He doesn't look like he'll be around for long. In " +
        "fact, since he's still around, why don't you report it " +
        "to the Guildmaster.\n");
}
