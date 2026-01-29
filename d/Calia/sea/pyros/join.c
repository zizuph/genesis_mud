

void do_join1(object ob);

int
do_join (string str)
{
    object shadow;

    if (str !="my life to Pyros")
    {
        notify_fail("Dedicate what?!\n");
       return 0;
    }

    seteuid(getuid());
    shadow = clone_object(FIRE_SHADOW);
    if (shadow->shadow_me(TP,GUILD_TYPE,GUILD_STYLE,GUILD_NAME) != 1)
    {
       NF("For some unknown reason you cannot join.\n");
       shadow->remove_shadow();
        write("You suddenly feel dizzy.\n");
        TP->move_living("M",CAVE+"room53");
       return 0;
    }
    TP->clear_guild_stat(SS_OCCUP);
    TP->set_skill(SS_PUNISHMENT,5);
    TP->remove_skill(SS_CARVED);
    present("worshipper_chalice",TP)->remove_object();
    present("worshipper_dagger",TP)->remove_object();
    present("worshipper_sceptre",TP)->remove_object();
    present("worshipper_wand",TP)->remove_object();
    present("worshipper_pentacle",TP)->remove_object();
    write("Your Elemental tools shatter into a thousand pieces!\n");
    if (TP->query_default_start_location() == WORSTART)
        TP->set_default_start_location(TP->query_def_start());
    TP->remove_guild_lay();
    TP->remove_cmdsoul(WORSHIPSOUL);
    TP->clear_guild_stat(SS_LAYMAN);
    write("A large crack appears in the floor beside you.  It "+
        "continues to grow wider and wider.  From it rises a large "+
        "flaming creature.\nThe large flaming creature "+
        "introduces himself as:\nLord Pyros, Elemental of Fire, "+
        "Lord of Flame.\nLord Pyros bellows: Greetings, "+
        (capitalize(TP->query_real_name()))+"!  Welcome to the Firewalkers!\n"+
        "Lord Pyros touches your forehead.\n");
    clone_object(FIRE_OBJECTS+"fwneck")->move(TP);
    clone_object(FIRE_OBJECTS+"walker_spells")->move(TP);
    set_alarm(2.0, 0.0, &do_join1(TP));
    return 1;
}

void
do_join1(object ob)
{
        ob->catch_msg("Lord Pyros hands you a necklace.\n");
    ob->add_cmdsoul(FIRE_SOUL);
    ob->set_skill(SS_WALKER_CHOSEN,SPELLS_ONE_FLAG);
    ob->update_hooks();
    present("_fchosen_",ob)->remove_object();
    ob->catch_msg("Lord Pyros bids you farewell.\nHe crawls back into "+
        "the crack beside you and it closes up behind him.  A "+
        "voice echos throughout the room 'Do not fear the flames!  "+
        "They shall hurt you no more!'.\n");
    ob->catch_msg("You boldy step through the flames and into the blood "+
        "red area.  Suddenly you find yourself back where you "+
        "began, in the room with the hand mark on the wall.\n");
    tell_room(CAVE+"room53","The north wall shimmers and turns a "+
        "blood red colour.  "+QCTNAME(ob)+" steps through.  The "+
        "wall returns to normal.\n");
    ob->move_living("M",CAVE+"room53");
    tell_room(CAVE+"joinroom",QCTNAME(ob)+" boldly steps through the "+
        "flames into the blood red area, and disappears.\n");
}
