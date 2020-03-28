import random

def gen_test_in():
    file = open('test_in_1.txt', 'w')

    num = 3
    file.write(str(num) + '\n')

    for i in range(num):
        for j in range(3):
            file.write(str(i * 3 + j + 1) + '\n');

    file.close()

def gen_data():
    file = open('data.txt', 'w')

    num = 33000
    file.write(str(num) + '\n')

    for i in range(num):
        file.write(str(random.randint(-10, 10) + random.random()) + ' ' +
                   str(random.randint(-10, 10) + random.random()) + ' ' +
                   str(random.randint(-10, 10) + random.random()) + '\n')

    file.close()
def gen_data_big():
    file = open('data_big.txt', 'w')

    num = 330000
    file.write(str(num) + '\n')

    for i in range(num):
        file.write(str(random.randint(-10, 10) + random.random()) + ' ' +
                   str(random.randint(-10, 10) + random.random()) + ' ' +
                   str(random.randint(-10, 10) + random.random()) + '\n')

    file.close()
def gen_data_big_big():
    file = open('data_big_big.txt', 'w')

    num = 3300000
    file.write(str(num) + '\n')

    for i in range(num):
        file.write(str(random.randint(-10, 10) + random.random()) + ' ' +
                   str(random.randint(-10, 10) + random.random()) + ' ' +
                   str(random.randint(-10, 10) + random.random()) + '\n')

    file.close()
def gen_data_big_big_big():
    file = open('data_big_big_big.txt', 'w')

    num = 33000000
    file.write(str(num) + '\n')

    for i in range(num):
        file.write(str(random.randint(-10, 10) + random.random()) + ' ' +
                   str(random.randint(-10, 10) + random.random()) + ' ' +
                   str(random.randint(-10, 10) + random.random()) + '\n')

    file.close()

def main():
    gen_test_in()
    gen_data()
    gen_data_big()
    gen_data_big_big()
    gen_data_big_big_big()

if __name__ == '__main__':
    main()
