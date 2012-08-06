#pragma once
template<class T, int i>

class MMBuffer : public MMObject
{
protected:
	T buffer[i];
public:
	inline T& operator [](int index)
	{
		assert(index < i && "Out-of-bounds index on MMBuffer::[]");
		return buffer[index];
	}

	inline operator T*()
	{
		return buffer;
	}

	AUTO_SIZE;
};

template<class T>

class MMDynamicBuffer : public MMObject
{
protected:
	unsigned long dataSize;
	T* buffer;
public:
	inline T& operator [](int index)
	{
		assert(index < dataSize && "Out-of-bounds index on MMDynamicBuffer::[]");
		return buffer[index];
	}

	inline operator T*()
	{
		return buffer;
	}

	MMDynamicBuffer(unsigned long size)
	{
		dataSize = size;
		buffer = new T[size];
		assert(buffer != 0 && "MMDynamicBuffer could not be created");
	}

	~MMDynamicBuffer()
	{
		if(buffer) delete[] buffer;
	}

	unsigned long size()
	{
		return dataSize+sizeof(this);
	}

	unsigned long bufferSize()
	{
		return dataSize;
	}
};