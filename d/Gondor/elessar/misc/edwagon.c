inherit "/d/Gondor/elessar/lib/wagon";

create_object()
{
  set_horses(4);
  set_name("wagon");
  add_name("carriage");
  add_name("horse carriage");
  add_name("edoras_minas_wagon");
  set_tour_file("/d/Gondor/elessar/misc/edorasminas");
  set_wagon_inside("/d/Gondor/elessar/misc/edinwagon");
  set_max_horses(4);
  set_max_livings(4);
  set_one_tour();
  make_wagon();
}
