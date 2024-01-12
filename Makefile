CFLAGS = -Wall -g
CPPFLAGS = -Wall -g
TARGET = transform

run: $(TARGET) 
		./$(TARGET) 

clean:
	rm $(TARGET)