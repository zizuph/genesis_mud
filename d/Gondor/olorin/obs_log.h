#define OBSOLETE_LOG "/d/Gondor/log/obsolete"

void
log_me()
{
  seteuid(getuid());
  write_file(OBSOLETE_LOG,
    file_name(this_object()) + " " + ctime(time()) + " " + 
    file_name(environment(this_object())) + "\n");
}
