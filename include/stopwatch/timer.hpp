/// @file timer.hpp
/// @author Enrico Fraccaroli (enry.frak@gmail.com)
/// @brief Benchmarking classes.

#pragma once

#include "stopwatch/duration.hpp"

namespace stopwatch
{

class Timer {
public:
    /// @brief Constructs a Timer object.
    /// @param print_mode The mode for printing the duration (default is human-readable).
    /// @param format The format to be used for printing (default is an empty string).
    Timer(PrintMode print_mode = human, const std::string &format = std::string())
        : _initial_time_point(clock_type_t::now()),
          _total_duration(Duration::zero(), print_mode, format),
          _print_mode(print_mode),
          _format(format)
    {
        // Nothing to do.
    }

    /// @brief Sets the print mode for the Timer.
    /// @param print_mode The new print mode to set.
    inline void set_print_mode(PrintMode print_mode)
    {
        _print_mode = print_mode;
        _total_duration.set_print_mode(print_mode);
    }

    /// @brief Sets the format string for the Timer.
    /// @param format The format string to set.
    inline void set_format(const std::string &format)
    {
        _format = format;
        _total_duration.set_format(format);
    }

    /// @brief Resets the Timer, clearing the total duration and setting the
    /// start time to now.
    inline void reset()
    {
        _total_duration     = duration_type_t::zero();
        _initial_time_point = clock_type_t::now();
    }

    /// @brief Starts the Timer by setting the initial time point to now.
    inline void start()
    {
        _initial_time_point = clock_type_t::now();
    }

    /// @brief Stops the Timer, resets it, and returns the elapsed duration.
    /// @return The elapsed Duration since the timer started.
    inline Duration stop()
    {
        Duration elapsed = this->elapsed_total();
        this->reset();
        return elapsed;
    }

    /// @brief Returns the total elapsed time without resetting the Timer.
    /// @return The total elapsed Duration.
    inline Duration elapsed_total() const
    {
        return Duration(clock_type_t::now() - _initial_time_point, _print_mode, _format);
    }

    /// @brief Converts the Timer's total duration to a string.
    /// @return A string representation of the total duration.
    std::string to_string() const
    {
        return _total_duration.to_string();
    }

    /// @brief Prints the Timer's total duration to an output stream.
    /// @param lhs The output stream.
    /// @param rhs The Timer to print.
    /// @return The modified output stream.
    friend std::ostream &operator<<(std::ostream &lhs, const Timer &rhs)
    {
        lhs << rhs.to_string();
        return lhs;
    }

private:
    /// @brief The starting time point of the Timer.
    time_point_type_t _initial_time_point;
    /// @brief The total elapsed duration.
    Duration _total_duration;
    /// @brief The print mode (e.g., human-readable or numeric).
    PrintMode _print_mode;
    /// @brief The format string used for printing.
    std::string _format;
};

/// @brief Checks if the elapsed time of the Timer exceeds a given threshold in seconds.
/// @param timer The Timer object to track the elapsed time.
/// @param target_duration The target duration in seconds.
/// @return True if the elapsed time exceeds the target duration, otherwise false.
inline bool timer_has_elapsed(const Timer &timer, double target_duration)
{
    // Compare the elapsed time with the target duration.
    return timer.elapsed_total().count() > target_duration;
}

} // namespace stopwatch