/* -*- c++ -*- */
/*
 * Copyright 2009,2012 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_CHANNELS_CHANNEL_MODEL_IMPL_H
#define INCLUDED_CHANNELS_CHANNEL_MODEL_IMPL_H

#include <gr_top_block.h>
#include <blocks/add_cc.h>
#include <blocks/multiply_cc.h>
#include <analog/sig_source_c.h>
#include <analog/noise_source_c.h>
#include <channels/channel_model.h>
#include <filter/fractional_interpolator_cc.h>
#include <filter/fir_filter_ccc.h>

namespace gr {
  namespace channels {

    class CHANNELS_API channel_model_impl : public channel_model
    {
    private:
      blocks::add_cc::sptr d_noise_adder;
      blocks::multiply_cc::sptr d_mixer_offset;

      analog::sig_source_c::sptr d_freq_offset;
      analog::noise_source_c::sptr d_noise;

      filter::fractional_interpolator_cc::sptr d_timing_offset;
      filter::fir_filter_ccc::sptr d_multipath;

      std::vector<gr_complex> d_taps;

      void setup_rpc();

    public:
      channel_model_impl(double noise_voltage,
			 double frequency_offset,
			 double epsilon,
			 const std::vector<gr_complex> &taps,
			 double noise_seed);
      
      ~channel_model_impl();

      void set_noise_voltage(double noise_voltage);
      void set_frequency_offset(double frequency_offset);
      void set_taps(const std::vector<gr_complex> &taps);
      void set_timing_offset(double epsilon);

      double noise_voltage() const;
      double frequency_offset() const;
      std::vector<gr_complex> taps() const;
      double timing_offset() const;
    };

  } /* namespace channels */
} /* namespace gr */

#endif /* INCLUDED_CHANNELS_CHANNEL_MODEL_IMPL_H */