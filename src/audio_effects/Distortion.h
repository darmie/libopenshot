/**
 * @file
 * @brief Header file for Distortion audio effect class
 * @author 
 *
 * @ref License
 */

// Copyright (c) 2008-2019 OpenShot Studios, LLC
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef OPENSHOT_DISTORTION_AUDIO_EFFECT_H
#define OPENSHOT_DISTORTION_AUDIO_EFFECT_H
#define _USE_MATH_DEFINES

#include "../EffectBase.h"

#include "../Frame.h"
#include "../Json.h"
#include "../KeyFrame.h"
#include "../Enums.h"

#include <memory>
#include <string>
#include <math.h>
// #include <OpenShotAudio.h>


namespace openshot
{

	/**
	 * @brief This class adds a distortion into the audio
	 *
	 */
	class Distortion : public EffectBase
	{
	private:
		/// Init effect settings
		void init_effect_details();

	public:
		openshot::DistortionType distortion_type;
		Keyframe input_gain;	
		Keyframe output_gain;	
		Keyframe tone;

		/// Blank constructor, useful when using Json to load the effect properties
		Distortion();

		/// Default constructor
		///
		/// @param new_level The audio default distortion level (between 1 and 100)
		Distortion(openshot::DistortionType new_distortion_type, Keyframe new_input_gain, Keyframe new_output_gain, Keyframe new_tone);

		/// @brief This method is required for all derived classes of ClipBase, and returns a
		/// new openshot::Frame object. All Clip keyframes and effects are resolved into
		/// pixels.
		///
		/// @returns A new openshot::Frame object
		/// @param frame_number The frame number (starting at 1) of the clip or effect on the timeline.
		std::shared_ptr<openshot::Frame> GetFrame(int64_t frame_number) override { 
			return GetFrame(std::make_shared<openshot::Frame>(), frame_number); 
		}

		/// @brief This method is required for all derived classes of ClipBase, and returns a
		/// modified openshot::Frame object
		///
		/// The frame object is passed into this method and used as a starting point (pixels and audio).
		/// All Clip keyframes and effects are resolved into pixels.
		///
		/// @returns The modified openshot::Frame object
		/// @param frame The frame object that needs the clip or effect applied to it
		/// @param frame_number The frame number (starting at 1) of the clip or effect on the timeline.
		std::shared_ptr<openshot::Frame> GetFrame(std::shared_ptr<openshot::Frame> frame, int64_t frame_number) override;

		// Get and Set JSON methods
		std::string Json() const override; ///< Generate JSON string of this object
		void SetJson(const std::string value) override; ///< Load JSON string into this object
		Json::Value JsonValue() const override; ///< Generate Json::Value for this object
		void SetJsonValue(const Json::Value root) override; ///< Load Json::Value into this object

		/// Get all properties for a specific frame (perfect for a UI to display the current state
		/// of all properties at any time)
		std::string PropertiesJSON(int64_t requested_frame) const override;

		class Filter : public juce::IIRFilter
		{
		public:
			void updateCoefficients(const double discrete_frequency, const double gain);
		};

		juce::OwnedArray<Filter> filters;

		void updateFilters(int64_t frame_number);
	};

}

#endif
