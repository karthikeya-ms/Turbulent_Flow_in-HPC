#pragma once

#include "Definitions.hpp"
#include "FieldStencil.hpp"
#include "TurbulentFlowField.hpp"
#include "Parameters.hpp"

namespace Stencils {

  /** Stencil for writting VTK files
   *
   * When iterated with, creates a VTK file.
   */
  class TurbulentVTKStencil: public FieldStencil<TurbulentFlowField> {
  private:
    bool          written_; //! Whether the file has already been written
    std::string   prefix_;  //! Prefix to be attached to the vtk files
    std::ofstream ofile_;   //! Output file stream

    std::stringstream pressureStream_; //! Stream for the pressure data
    std::stringstream velocityStream_; //! Stream for the velocity data
    std::stringstream turbViscStream_; //! Stream for the velocity data
    
    std::stringstream tauStream_; //! Stream for the tau data
    std::stringstream uPlusStream_; //! Stream for the uPlus data
    std::stringstream yPlusStream_; //! Stream for the yPlus data

    void writeVTKHeader(std::ostream& file) const;
    void writePoints(std::ostream& file, RealType simulationTime) const;

    /** Open output file
     * Opens the output file and prepares for writing.
     * It also writes the header of the file and the points of the grid.
     * @param timeStep Current time step of the simulation
     * @param simulationTime Current simulation time in double format
     */
    void openFile(int timeStep, RealType simulationTime);

    /** Finish writing. Must be called once the file has been written.
     *
     * Stores all the streams and closes the file.
     */
    void closeFile();

  public:
    TurbulentVTKStencil(const Parameters& parameters);
    ~TurbulentVTKStencil() override = default;

    void apply(TurbulentFlowField& flowField, int i, int j) override;
    void apply(TurbulentFlowField& flowField, int i, int j, int k) override;

    void write(TurbulentFlowField& flowField, int timeStep, RealType simulationTime);
  };

} // namespace Stencils
