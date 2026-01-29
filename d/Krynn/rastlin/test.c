test()
{
    object c;
    object a, b;
    a = clone_object("/d/Krynn/std/aurak");
    b = clone_object("/d/Rhovanion/lib/rumour_sh");
    c = clone_object("/d/Krynn/std/sivak");
    b->shadow_me(a);
    a->set_up_rumour(c, "That Teth is no good in bed.", "Kitiara", time());
    c->move(environment(find_player("rastlin")));
    a->move(environment(find_player("rastlin")));
}
