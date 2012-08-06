#pragma once
template<class T, unsigned long bufSize>

class RingBuffer
{
protected:
	T buf[bufSize];
	unsigned long read, write;

public:
	RingBuffer(void)
	{
		read = 0;
		write = 1;
	}

	bool operator << (T& obj)
	{
		buf[write] = obj;
		if (write + 1 % bufSize == read) return false;
		write = write + 1 % bufSize;
		return true;
	}

	bool operator >> (T& res)
	{
		read = read + 1 % bufSize;
		if (read == write) {
			write = write + 1 % bufSize;
			return false;
		}
		res = buf[read];
		return true;
	}

	unsigned long dataSize()
	{
		unsigned long wc = write;
		while (wc < read) wc += bufSize;
		return wc - read - 1;
	}

	void fill(const T& value)
	{
		for (write = 0; write < bufSize; write++) {
			buf[write] = value;
		}
		read = 0;
		write = 1;
	}
};