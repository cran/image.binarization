// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef SAUVOLA_HPP
#define SAUVOLA_HPP

#include "Algorithm.hpp"
#include "LocalWindow.hpp"
#include "MeanVarianceCalculator.hpp"


namespace Doxa
{
	/// <summary>
	/// The Sauvola Algorithm: J. Sauvola, M. Pietikäinen
	/// </summary>
	/// <remarks>"Adaptive document image binarization", 1999.</remarks>
	class Sauvola : public Algorithm<Sauvola>, public MeanVarianceCalculator
	{
	public:
		void Initialize(const Image& grayScaleImageIn)
		{
			Algorithm::Initialize(grayScaleImageIn);
			MeanVarianceCalculator::Initialize(grayScaleImageIn);
		}

		void ToBinary(Image& binaryImageOut, const Parameters& parameters = Parameters())
		{
			double mean, stddev;

			// Read parameters, utilizing defaults
			const int windowSize = parameters.Get("window", 75);
			const double k = parameters.Get("k", 0.2);

			LocalWindow::Process(binaryImageOut, Algorithm::grayScaleImageIn, windowSize, [&](const Region& window, const int&) {
				CalculateMeanStdDev(mean, stddev, window);

				return mean * (1 + k * ((stddev / 128) - 1));
			});
		}
	};
}


#endif //SAUVOLA_HPP
