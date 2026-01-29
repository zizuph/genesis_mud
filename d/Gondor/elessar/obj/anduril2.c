inherit "/obj/weapon.c";

int magic_hit;

reset(arg)
{

	if (arg)
		return;

	set_name("Anduril");
	set_alias("sword");
	set_short("Elessar's sword Anduril");
	set_long("It's the Anduril, the Sword that was broken!\n" +
		 "It is now forged anew by Elrond's elves, and is\n" +
		 "Elessar's trusted weapon against the evils forces.\n" +
		 "The contours of a tree surrounded by seven stars\n" +
		 "are engraved in the blade.\n");
	set_class(20);
	set_weight(4);
	set_value(15000);
	set_hit_func(this_object());

	magic_hit = 20 + random(20);

}

weapon_hit()
{

	if (!magic_hit)
		return;

	if (random(5) == 0)
	{
		magic_hit--;

		write("You shout 'By Elendil!!' as you hit your foe.\n");
		say("You feel a stunning shock as the sword Anduril hits you!\n");
		this_player()->query_attack()->hit_player(random(10) + 5);
	}

	if (!magic_hit)
	{
		write("Your sword, Anduril breaks in two pieces!!\n");
		set_class(1);
		set_weight(4);
		set_value(20);
		set_short("The shards of Anduril");
		set_long("Anduril, the sword that is broken. It looks quite useless.\n");
		un_wield();
	}

}

wield()
{

	if(magic_hit)
		write("You feel a magical shock rush through your body!\n");

	::wield();

	return 1;

}

un_wield()
{

	if(magic_hit)
		write("You feel less powerful now.\n");

	::un_wield();

	return 1;

}

