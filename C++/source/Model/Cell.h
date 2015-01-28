/**
 * @file    Cell.h
 * @brief   1細胞（1セル）を管理するクラスの宣言.
 */

#ifndef __CELL_H__
#define __CELL_H__

#include "../Lib/Observer.h"
#include "CellAttribute.h"

// クラスの前方宣言.
class MatrixCell;

/**
 * @brief 細胞（セル）1個をあらわすクラス.
 */
class Cell : public Subject
{
public:
    /**
     * @brief   隣接セルの方向と番号の定義.
     * @note    隣接セルの方向と番号を以下のように定義する.(selfは自分自身).<br>
     *          <table border="1">
     *              <tr><td>0:TOP_LEFT</td><td>1:TOP_MIDDLE</td><td>2:TOP_RIGHT</td>
     *              <tr><td>3:LEFT</td><td>self</td><td>4:RIGHT</td>
     *              <tr><td>5:BOTTOM_LEFT</td><td>6:BOTTOM_MIDDLE</td><td>7:BOTTOM_RIGHT</td>
     *          </table>
     */
    enum NEIGHBOR_POSITION
    {
        TOP_LEFT=0,     TOP_MIDDLE,     TOP_RIGHT, 
        LEFT,                           RIGHT,
        BOTTOM_LEFT,    BOTTOM_MIDDLE,  BOTTOM_RIGHT,
        NEIGHBOR_MAX
    };

    /**
     * @brief   コンストラクタ.
     * @param   long i_lCol 座標位置 横方向.
     * @param   long i_lRow 座標位置 縦方向.
     */
    Cell(long i_lCol, long i_lRow);

    /**
     * @brief   デストラクタ.
     */
    virtual ~Cell();

    /**
     * @brief   初期化.
     * @param   long i_lCol 座標位置 横方向.
     * @param   long i_lRow 座標位置 縦方向.
     * @return  なし.
     */
    void init(long i_lCol, long i_lRow);

    /**
     * @brief   セルの座標位置(横方向)を設定.
     * @param   long i_lCol 座標位置(横方向).
     * @return  なし.
     */
    void setCol(long i_lCol)
    {
        m_cAttribute.setCol(i_lCol);
    }

    /**
     * @brief   セルの座標位置(横方向)を取得.
     * @param   なし.
     * @return  セルの座標位置(横方向).
     */
    long getCol() const
    {
        return (m_cAttribute.getCol());
    }

    /**
     * @brief   セルの座標位置(縦方向)を設定.
     * @param   long i_lCol 座標位置(縦方向).
     * @return  なし.
     */
    void setRow(long i_lRow)
    {
        m_cAttribute.setRow(i_lRow);
    }

    /**
     * @brief   セルの座標位置(縦方向)を取得.
     * @param   なし.
     * @return  セルの座標位置(縦方向).
     */
    long getRow() const
    {
        return (m_cAttribute.getRow());
    }

    /**
     * @brief   自分自身のセルの状態を取得.
     * @param   なし.
     * @return  セルの状態.(DEAD/ALIVE).
     * @retval  DEAD    死滅.
     * @retval  ALIVE   生存.
     */
    CellAttribute::CELL_STATE getState() const
    {
        return (m_cAttribute.getState());
    }

    /**
     * @brief   自分自身のセルの状態を設定.
     * @param   CellAttribute::CELL_STATE i_eState 設定したい状態.
     * @return  なし.
     */
    void setState(CellAttribute::CELL_STATE i_eState)
    {
        m_cAttribute.setState(i_eState);
    }

    /**
     * @brief   隣接セルを設定する.
     * @param   MatrixCell* i_pcMatrixCell この引数から, 隣接セルを取得する
     * @return  なし.
     * @note    隣接セルの方向と番号は, NEIGHBOR_POSITIONを想定している.
     */
    void setNeighbor(MatrixCell* i_pcMatrixCell);

    /**
     * @brief   隣接セルに自分の状態を通知する.
     * @param   なし.
     * @return  通知に成功/失敗を返す.
     * @retval  true    成功.
     * @retval  false   失敗.
     */
    bool sendStateToNeighborCell();

    /**
     * @brief   自分自身の状態を決定する.
     * @param   なし.
     * @return  前状態から変更があったかを返す.
     * @retval  true    変更有り.
     * @retval  false   変更無し.
     * @note    隣接セルの状態から自分自身の状態を決定する.<br>
     *          記憶していた隣接セルの状態をクリアする.<br>
     */
    bool decideState();

private:
    
    /**
     * @brief   自分自身のセルの属性.
     * @note    座標位置と状態を保持する.
     */
    CellAttribute m_cAttribute;

    /**
     * @brief   隣接セルの状態数.
     * @note    m_rglNeighborStateNum[CellAttribute::DEAD]  隣接セルの死滅数.
     * @note    m_rglNeighborStateNum[CellAttribute::ALIVE] 隣接セルの生存数.
     */
    long m_rglNeighborStateNum[CellAttribute::CELL_STATE_MAX];

    /**
     * @brief   隣接セルへのポインタ.
     * @see     隣接セルの方向は, NEIGHBOR_POSITIONを参照.
     */
    Cell* m_pcNeighborCell[NEIGHBOR_MAX];

    /**
     * @brief   自分自身と隣接セルの状態から, 誕生か否かを判定する.
     * @param   なし.
     * @return  セルの状態がALIVEとなるかを返す.
     * @retval  true    セルの状態がALIVEとなる.
     * @retval  false   セルの状態は変更無し.
     * @note    死んでいるセルに隣接する生きたセルがちょうど3つあれば,次の世代が誕生する.
     */
    bool isBorn();

    /**
     * @brief   自分自身と隣接セルの状態から, 生存か否かを判定する.
     * @param   なし.
     * @return  セルの状態がALIVEとなるかを返す.
     * @retval  true    セルの状態がALIVEとなる.
     * @retval  false   セルの状態は変更無し.
     * @note    生きているセルに隣接する生きたセルが2つか3つならば, 次の世代でも生存する.
     */
    bool isSurvive();

    /**
     * @brief   自分自身と隣接セルの状態から, 過疎か否かを判定する.
     * @param   なし.
     * @return  セルの状態がDEADとなるかを返す.
     * @retval  true    セルの状態がDEADとなる.
     * @retval  false   セルの状態は変更無し.
     * @note    生きているセルに隣接する生きたセルが1つ以下ならば, 過疎により死滅する.
     */
    bool isUnderPopulation();

    /**
     * @brief   自分自身と隣接セルの状態から, 過密か否かを判定する.
     * @param   なし.
     * @return  セルの状態がDEADとなるを返す.
     * @retval  true    セルの状態がDEADとなる.
     * @retval  false   セルの状態は変更無し.
     * @note    生きているセルに隣接する生きたセルが4つ以上ならば, 過密により死滅する.
     */
    bool isOverPopulation();

    /**
     * @brief   隣接セルの状態を受け取る.
     * @param   CellAttribute::CELL_STATE i_eState 隣接セルの状態(DEAD/ALIVE)
     * @return  結果.
     * @retval  true    成功.
     * @retval  false   失敗.
     */
    bool receiveStateFromNeighborCell(CellAttribute::CELL_STATE i_eState);

    /**
     * @brief   境界値をチェックする.
     * @param   long i_lValue   チェックしたい値.
     * @param   long i_lMax     チェックしたい値の最大値.
     * @note    引数i_lValueが境界値だった場合, 以下とする.
     *              ・最大値 = 最小値(0).
     *          つまり, 境界値は存在せず(2次元の場合)球面とする.
     */
    long checkRegion(long i_lValue, long i_lMax);

};

#endif  //__CELL_H__
