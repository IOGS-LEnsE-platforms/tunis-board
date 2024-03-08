TUNIS board description
=======================

Signal processing
-----------------

In this section, the **signal processing** part of the board will be described.

.. figure:: ../_static/TUNIS_board_analog.png
   :alt: TUNIS board - Analog inputs and outputs
   :align: center
   :width: 90%
   
   TUNIS board - Analog inputs and outputs

Inputs
~~~~~~

.. caution::
   Analog and digital inputs of a STM32 microcontroller (included on the Nucleo board) operate on voltages between **0 and 3.3V**. Otherwise inputs can lead to severe damages.

Outputs
~~~~~~~




DC Motor position control
-------------------------

In this section, the **DC motor position control** part of the board will be described.

.. figure:: ../_static/TUNIS_board_DC_motor.png
   :alt: TUNIS board - DC motor connector
   :align: center
   :width: 90%
   
   TUNIS board - DC motor connector


Connection to the motor
~~~~~~~~~~~~~~~~~~~~~~~

During labworks, **Pololu** DC motor (*3239* or *4843*) are used.  This gearmotor consists of a **12 V** brushed DC motor combined with a 20.4:1 metal gearbox. A 48 CPR quadrature encoder is integrated on the motor shaft. It provides 979.62 counts per revolution of the gearbox’s output shaft.
 

More documentation is available at the `Pololu website <https://www.pololu.com/>`_ : `POL3239 <https://www.pololu.com/product/3239>`_ or `POL4843 <https://www.pololu.com/product/4843>`_

.. figure:: ../_static/pololu_connector.jpg
   :alt: Pololu DC motor connector - From pololu.com
   :align: center
   :width: 90%
   
   Pololu DC motor connector - From pololu.com

.. flat-table:: Pololu DC motor connector - From pololu.com
   :widths: 20 30
   :header-rows: 1

   * - Color
     - Function
   * - Red
     - Motor power (connected to one motor terminal)
   * - Black
     - Motor power (connected to the other motor terminal)
   * - Green
     - Encoder GND
   * - Blue
     - Encoder VCC (5V)
   * - Yellow
     - Encoder A output
   * - White
     - Encoder B output

Power supplies
~~~~~~~~~~~~~~

.. caution::
   Pololu motors *3239* and *4843* support a voltage until 12V.