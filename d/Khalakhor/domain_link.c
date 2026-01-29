inherit "/std/domain_link";

public void
preload_link()
{
    preload("/d/Khalakhor/sys/global/random");
    preload("/d/Khalakhor/common/obj/information_master");
    preload("/d/Khalakhor/common/herbs/herb_master");
    preload("/d/Khalakhor/sys/global/clock");

    // Training rooms 
    preload("/d/Khalakhor/guilds/racial/eilgalaith/room/train");
    preload("/d/Khalakhor/guilds/racial/eilgalaith/room/garden");

    /* Shiplines */
    preload("/d/Khalakhor/ship/macdunn/pier2");
    preload("/d/Khalakhor/ship/macdunn/pier4");
    preload("/d/Khalakhor/ship/macdunn/pier6");
    preload("/d/Khalakhor/ship/macdunn/pier8");
    preload("/d/Khalakhor/ship/macdunn/pier10");
    preload("/d/Khalakhor/ship/macdunn/pier12");
    preload("/d/Khalakhor/inisi/roke/nyreese/cadu_b2");
}

public void
armageddon(int level)
{
    ("/d/Khalakhor/sys/global/clock")->save_clock();
}
