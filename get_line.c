#include "shell.h"

/**
 * input_buf - Buffer chain comds.
 * @info: Param structure.
 * @buf: Buffer address.
 * @len: Address len_var.
 * Return: Read bytes.
 * Tinnie and Jay.
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)

{
	ssize_t re = 0;
	size_t len_p = 0;

	if (!*len)
	{

		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		re = getline(buf, &len_p, stdin);
#else
		re = _getline(info, buf, &len_p);
#endif
		if (re > 0)
		{
			if ((*buf)[re - 1] == '\n')
			{
				(*buf)[re - 1] = '\0';
				re--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			
			{
				*len = re;
				info->cmd_buf = buf;
			}
		}
	}
	return (re);
}

/**
 * get_input - Fetch line - the \n.
 * @info: Param structure.
 * Return: Bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t in, je, len;
	ssize_t re = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (re == -1)
		return (-1);
	if (len)
	{
		je = in;
		p = buf + in;

		check_chain(info, buf, &je, in, len);
		while (je < len)
		{
			if (is_chain(info, buf, &je))
				break;
			je++;
		}

		in = je + 1;
		if (in >= len)
		{
			in = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (re);
}

/**
 * read_buf - Read buffer.
 * @info: Param struct.
 * @buf: Buffer.
 * @i: size.
 * Return: re
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)

{
	ssize_t re = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (re >= 0)
		*i = re;
	return (re);
}

/**
 * _getline - Next line of input from stdin.
 * @info: param structure.
 * @ptr: Address of pointer 2 buffer.
 * @length: Size pointetr buffer not NULL.
 * Return: s.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t in, len;
	size_t kt;
	ssize_t re = 0, st = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		st = *length;
	if (in == len)
		in = len = 0;

	r = read_buf(info, buf, &len);
	if (re == -1 || (re == 0 && len == 0))
		return (-1);

	c = _strchr(buf + in, '\n');
	kt = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, st, st ? st + kt : kt + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + in, kt - i);
	else
		_strncpy(new_p, buf + in, kt - in + 1);

	st += kt - i;
	in = kt;
	p = new_p;

	if (length)
		*length = st;
	*ptr = p;
	return (st);
}

/**
 * sigintHandler - Blocks ctrl-C.
 * @sig_num: Signal number.
 * Return: Void.
 */

void sigintHandler(__attribute__((unused))int sig_num)

{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
