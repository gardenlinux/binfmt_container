#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <stddef.h>

#include <sys/mount.h>
#include <sys/stat.h>

int main()
{
	int fd;

	if (mkdir("/binfmt_misc", 0700) == -1) err(1, "mkdir /binfmt_misc");
	if (mount("", "/binfmt_misc", "binfmt_misc", 0, 0) == -1) err(1, "mount binfmt_misc");

	if ((fd = open("/binfmt_misc/register", O_WRONLY)) == -1) err(1, "open /binfmt_misc/register");
	char str[] = ":qemu-aarch64:M::\\x7f\\x45\\x4c\\x46\\x02\\x01\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x02\\x00\\xb7\\x00:\\xff\\xff\\xff\\xff\\xff\\xff\\xff\\x00\\xff\\xff\\xff\\xff\\xff\\xff\\xff\\xff\\xfe\\xff\\xff\\xff:/aarch64-binfmt-P:POCF";
	size_t len = sizeof(str) - 1;
	if (write(fd, str, len) != (ssize_t) len) err(1, "write /binfmt_misc/register");

	close(fd);

	umount("/binfmt_misc");
	rmdir("/binfmt_misc");
	return 0;
}
