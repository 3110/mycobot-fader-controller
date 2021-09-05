#ifndef MOVING_MEAN_H_
#define MOVING_MEAN_H_

#include <array>

template <class T = uint16_t, std::size_t WINDOW_SIZE = 3>
class MovingMean {
public:
    MovingMean(void)
        : firstTime(true),
          window{
              0,
          },
          pos(0),
          sum(0) {
    }

    ~MovingMean(void) {
    }

    T update(T v) {
        if (firstTime) {
            firstTime = false;
            window.fill(v);
            sum = v * WINDOW_SIZE;
        } else {
            sum -= window[pos];
            window[pos] = v;
            sum += v;
        }
        pos = (pos + 1) % WINDOW_SIZE;
        return get();
    }

    inline T get(void) const {
        return static_cast<T>(sum / WINDOW_SIZE);
    }

    void dump(HardwareSerial& s) {
        s.print("[");
        s.print(window[0]);
        for (int i = 1; i < WINDOW_SIZE; ++i) {
            s.print(", ");
            s.print(window[i]);
        }
        s.print("] -> ");
        s.println(get());
    }

private:
    bool firstTime;
    std::array<T, WINDOW_SIZE> window;
    size_t pos;
    double sum;
};

#endif